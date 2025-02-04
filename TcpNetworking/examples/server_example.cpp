#include <iostream>

#include "../include/tcpServer.h"

int main()
{
    TcpServer server(8080);

    if (!server.start()) {
        std::cerr << "Failed to start server\n";
        return 1;
    }

    std::cout << "Server is listening on port 8080...\n";

    while (true)
    {
        if (server.has_pending_connections())
        {
            auto client = server.accept_client();
            if (client)
            {
                std::cout << "Client connected from: " << client->get_peer_name() << "\n";
                client->send_data("Hello, client!");
            }
        }
    }

    server.close_server();
    return 0;
}

