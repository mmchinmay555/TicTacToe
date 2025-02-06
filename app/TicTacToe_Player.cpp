#include "TicTacToe_Client.h"

int main()
{
    std::string ip = "127.0.0.1"; // Server address
    int port = 8080;              // Server port

    TTT_Player *player = new TTT_Player(port, ip);
    player->enter_game();

    return 0;
}
