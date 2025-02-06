#include "TicTacToe_Client.h"

TTT_Player::TTT_Player(int server_port, const std::string server_ip)
    : TcpClient()
    , server_port(server_port)
    , server_ip(server_ip)
    , is_game_running(false)
{

}

void TTT_Player::enter_game()
{
    if (join_game())
    {
        start_playing();
    }
    else
    {
        std::cerr << "Unable to join game" << std::endl;
    }
}

bool TTT_Player::join_game()
{
    if (!this->connect_to_server(server_port, server_ip))
    {
        std::cerr << "Failed to connect to server!" << std::endl;
        return false;
    }

    is_game_running = true;
    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;
    return true;
}

void TTT_Player::exit_game()
{
    close_connection();
    is_game_running = false;

    std::cout << "bye..!" << std::endl;
}

void TTT_Player::reciever_job()
{
    while (is_game_running)
    {
        if (this->ready_read())
        {
            std::string response = this->receive_data();
            if (!response.empty())
            {
                std::cout << "\n" << response << std::flush;
            }
        }
    }
}

void TTT_Player::sender_job()
{
    while (is_game_running)
    {
        std::string msg;
        std::getline(std::cin, msg);

        if (msg == "quit") break;

        if (!msg.empty())
        {
            if (!this->send_data(msg))
            {
                std::cerr << "Failed to send data!" << std::endl;
            }
        }
    }
}

void TTT_Player::start_playing()
{
    std::thread recv_thread([this]()
    {
        reciever_job();
    });

    // Take Input for Play from User
    sender_job();

    exit_game();
    recv_thread.join();
}
