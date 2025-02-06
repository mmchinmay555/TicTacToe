#include "GameServer.h"


GameServer::GameServer(int port)
    : port(port)
    , server(new TcpServer(port))
    , waiting_player_id(-1)
    , is_game_server_running(false)
{

}

GameServer::~GameServer()
{
    delete server;
}

void GameServer::start_server()
{
    if (server)
    {
        if (server->start())
        {
            is_game_server_running = true;
            start_lobby();
        }
    }
}

void GameServer::close_server()
{
    if (server)
    {
        server->close_server();
    }

    is_game_server_running = false;
}

void GameServer::send_message_to_player(int player_id, const std::string &message)
{
    if (players.find(player_id) != players.end())
    {
        // std::cout << "Msg sent to " << player_id << ", msg: " << message << std::endl;
        players[player_id].send_data(message);
    }
    else
    {
        std::cerr << player_id << " - NOT VALID player_id | " << "msg: " << message << std::endl;
    }
}

void GameServer::start_lobby()
{
    if (!server)
    {
        return;
    }

    // Start the player communication thread
    std::thread player_communication_thread([this]()
    {
        start_communication();
    });

    // Main loop to handle incoming connections
    while (is_game_server_running)
    {
        if (server->has_pending_connections())
        {
            auto client = server->accept_client();
            if (client)
            {
                handle_new_player_connection(std::move(client));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    player_communication_thread.join();
}

void GameServer::start_communication()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        for (auto& player : players)
        {
            if (player.second.ready_read())
            {
                std::string msg_from_client = player.second.read_data();

                // If msg is empty then, player has disconnected
                if (msg_from_client.empty())
                {
                    handle_player_disconnection(player.first);
                    break;
                }

                forward_message_to_opponent(player.first, msg_from_client);
            }
        }
    }
}

void GameServer::handle_new_player_connection(std::unique_ptr<Socket> player_socket)
{
    int player_id = player_socket->get_socket_fd();

    Player new_player(player_id, std::move(player_socket));
    add_player_to_map(new_player);
}

void GameServer::add_player_to_map(Player &player)
{
    int player_id = player.get_id();
    {
        std::lock_guard<std::mutex> lock(mtx);
        players[player_id] = std::move(player);
    }

    std::cout << "player_" << player_id << " joined" << std::endl;

    // Send a welcome message to the connected player
    std::string msg = "You are player_" + std::to_string(player_id);
    send_message_to_player(player_id, msg);

    // Match with an opponent
    match_player(player_id);
}

void GameServer::forward_message_to_opponent(int player_id, const std::string &msg)
{
    if (players[player_id].get_is_allowed_to_play())
    {
        int opponent_player_id = players[player_id].get_opponent_id();

        if (opponent_player_id != -1)
        {
            std::string reply;

             // Asking to validate;
            if (!validate_input(player_id, msg))
            {
                send_message_to_player(player_id, "Invalid move!\nEnter msg: ");
                return;
            }

            int status = update_move_and_get_reply(player_id, msg, reply);

            send_message_to_player(player_id, "Your > " + reply);
            send_message_to_player(opponent_player_id, "player > " + reply);

            std::string curr_state = "";
            get_current_data(player_id, curr_state);

            if (status == 0)
            {
                // 0  : No winner
                send_message_to_player(player_id, "GAME ENDED, NO WINNER :|\nNEW GAME BEGINS..!");
                send_message_to_player(opponent_player_id, "GAME ENDED, NO WINNER :|\nNEW GAME BEGINS..!");

                send_message_to_player(player_id, curr_state);
                send_message_to_player(opponent_player_id, curr_state);
            }
            else if (status == 1)
            {
                // 1  : player_id WON, opponent LOOSE
                send_message_to_player(player_id, "GAME ENDED, YOU WON!\nNEW GAME BEGINS..!");
                send_message_to_player(opponent_player_id, "GAME ENDED, YOU LOOSE :(\nNEW GAME BEGINS..!");

                send_message_to_player(player_id, curr_state);
                send_message_to_player(opponent_player_id, curr_state);
            }
            else if (status == 2)
            {
                // 2  : player_id LOOSE, opponent WON
                send_message_to_player(player_id, "GAME ENDED, YOU LOOSE :(\nNEW GAME BEGINS..!");
                send_message_to_player(opponent_player_id, "GAME ENDED, YOU WON!\nNEW GAME BEGINS..!");

                send_message_to_player(player_id, curr_state);
                send_message_to_player(opponent_player_id, curr_state);
            }
            else if (status == -1)
            {
                // -1 : Match in progress, no need to do anything
            }
        }

        {
            std::lock_guard<std::mutex> lock(mtx);

            players[player_id].set_is_allowed_to_play(false);
            if (players.find(opponent_player_id) != players.end())
            {
                players[opponent_player_id].set_is_allowed_to_play(true);
            }
        }

        // Notify allowed player to play
        send_message_to_player(players[player_id].get_opponent_id(), "Enter msg: ");
    }
}

void GameServer::handle_player_disconnection(int disconnected_player_id)
{
    std::cout << "player_" << disconnected_player_id << " ..left!" << std::endl;
    on_player_left(disconnected_player_id);
}

void GameServer::match_player(int player_id)
{
    if (waiting_player_id == -1)
    {
        waiting_player_id = player_id;
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(mtx);

            players[player_id].set_opponent_id(waiting_player_id);
            players[waiting_player_id].set_opponent_id(player_id);
        }

        waiting_player_id = -1;
    }

    if (players[player_id].get_opponent_id() != -1)
    {
        start_new_session(player_id, players[player_id].get_opponent_id());
    }
}

void GameServer::start_new_session(int player_1_id, int player_2_id)
{
    std::cout << "Session start for: " << " player_" << player_1_id << " - " << " player_" << player_2_id << std::endl;

    std::string msg = "New Game begins!";

    send_message_to_player(player_1_id, msg);
    send_message_to_player(player_2_id, msg);

    {
        std::lock_guard<std::mutex> lock(mtx);

        // First turn - player_1_id, Second turn - player_2_id;
        players[player_1_id].set_is_allowed_to_play(true);
        players[player_2_id].set_is_allowed_to_play(false);
    }

    game_started(player_1_id, player_2_id);

    std::string curr_state = "";
    get_current_data(player_1_id, curr_state);

    send_message_to_player(player_1_id, curr_state);
    send_message_to_player(player_2_id, curr_state);

    send_message_to_player(player_1_id, "Enter msg: ");
}

void GameServer::on_player_left(int player_id)
{
    // Waiting player left, do nothing
    if (waiting_player_id == player_id)
    {
        waiting_player_id = -1;
    }
    else
    {
        int opponent_id = players[player_id].get_opponent_id();
        game_ended(player_id, opponent_id);

        std::string msg = "Your opponent left, please wait till another player joins..";
        send_message_to_player(opponent_id, msg);

        {
            std::lock_guard<std::mutex> lock(mtx);
            players[opponent_id].set_opponent_id(-1);
        }

        match_player(opponent_id);
    }

    {
        std::lock_guard<std::mutex> lock(mtx);
        players.erase(player_id);
    }
}
