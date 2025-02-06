#include "TicTacToe_Server.h"

TTT_Server::TTT_Server(int port)
    : GameServer(port)
{

}

TTT_Server *TTT_Server::get_instance(int port)
{
    static TTT_Server* server = new TTT_Server(port);
    return server;
}

void TTT_Server::game_started(int player1_id, int player2_id)
{
    std::pair<int, int> paired_players = create_pair(player1_id, player2_id);

    if (player_to_pair_map.find(player1_id) == player_to_pair_map.end() && player_to_pair_map.find(player2_id) == player_to_pair_map.end())
    {
        // Map both players to the pair;
        player_to_pair_map[player1_id] = paired_players;
        player_to_pair_map[player2_id] = paired_players;
    }
    else
    {
        std::cerr << "SOME ERRR.. MATCHING" << std::endl;
    }

    if (players_to_session_map.find(paired_players) == players_to_session_map.end())
    {
        players_to_session_map[paired_players] = std::array<int, 9>();
    }
    else
    {
        std::cerr << "Trying to start the game again.." << std::endl;
    }
}

void TTT_Server::game_ended(int player1_id, int player2_id)
{
    std::pair<int, int> paired_players = create_pair(player1_id, player2_id);

    if (players_to_session_map.find(paired_players) != players_to_session_map.end())
    {
        players_to_session_map.erase(paired_players);
    }
    else
    {
        std::cerr << "Trying to end the game again.." << std::endl;
    }

    if (player_to_pair_map.find(player1_id) != player_to_pair_map.end() && player_to_pair_map.find(player2_id) != player_to_pair_map.end())
    {
        // Erase players map
        player_to_pair_map.erase(player1_id);
        player_to_pair_map.erase(player2_id);
    }
    else
    {
        std::cerr << "SOME ERRR.. MATCHING" << std::endl;
    }
}

void TTT_Server::handle_player_move(int player_id, const std::string &msg)
{
    if (std::stoi(msg) > 8) return;
    players_to_session_map[player_to_pair_map[player_id]][std::stoi(msg)] = player_id;
}

int TTT_Server::update_move_and_get_reply(int player_id, const std::string &msg, std::string &reply)
{
    handle_player_move(player_id, msg);

    reply.clear();

    for (auto i : players_to_session_map[player_to_pair_map[player_id]])
    {
        reply += std::to_string(i) + " ";
    }

    if (std::stoi(msg) == 100 || std::stoi(msg) == 200 || std::stoi(msg) == 300)
    {
        // GAME ENDED
        players_to_session_map[player_to_pair_map[player_id]].fill(0);

        if (std::stoi(msg) == 100)
        {
            // 0  : No winner
            return 0;
        }
        if (std::stoi(msg) == 200)
        {
            // 1  : player_id WON, opponent WON
            return 1;
        }
        if (std::stoi(msg) == 300)
        {
            // 2  : player_id LOOSE, opponent WON
            return 2;
        }
    }


    // -1 : Match in progress
    return -1;
}

std::pair<int, int> TTT_Server::create_pair(int player1_id, int player2_id)
{
    std::pair<int, int> players_pair;

    if (player1_id < player2_id)
    {
        players_pair = std::pair<int, int>(player1_id, player2_id);
    }
    else
    {
        players_pair = std::pair<int, int>(player2_id, player1_id);
    }

    return players_pair;
}
