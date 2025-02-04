#include <iostream>

#include "../include/tcpClient.h"

int main()
{
    TcpClient client;

    std::string server_ip = "127.0.0.1"; // Server address
    int server_port = 8080;              // Server port

    if (!client.connect_to_server(server_port, server_ip))
    {
        std::cerr << "Failed to connect to server!" << std::endl;
        return 1;
    }

    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;

    // Send a message to the server
    std::string message = "Hello, Server!";
    if (!client.send_data(message))
    {
        std::cerr << "Failed to send data!" << std::endl;
        return 1;
    }
    std::cout << "Message sent: " << message << std::endl;

    // Receive response from server
    std::string response = client.receive_data();
    if (!response.empty())
    {
        std::cout << "Server response: " << response << std::endl;
    }
    else
    {
        std::cerr << "No response from server." << std::endl;
    }

    // Close client connection
    client.close_connection();
    std::cout << "Client disconnected." << std::endl;

    return 0;
}
