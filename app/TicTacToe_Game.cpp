#include "TicTacToe_Server.h"

int main() {
    TTT_Server *server = TTT_Server::get_instance(8080);
    server->start_server();

    return 0;
}
