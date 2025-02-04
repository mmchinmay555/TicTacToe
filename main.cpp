#include <iostream>

using namespace std;
#include "gameServer.h"

int main()
{
    GameServer server(8080);
    server.start_server();

    return 0;
}
