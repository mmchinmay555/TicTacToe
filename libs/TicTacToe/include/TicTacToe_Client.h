#include <iostream>

#include "TcpClient.h"

#include <thread>

class TTT_Player : public TcpClient
{
private:
    const std::string server_ip;  // Server address
    const int server_port;        // Server port

    bool is_game_running;

public:
    TTT_Player(int server_port, const std::string server_ip);
    void enter_game();

private:
    bool join_game();
    void exit_game();

    void start_playing();
    void reciever_job();
};
