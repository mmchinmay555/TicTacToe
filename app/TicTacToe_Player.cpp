//#include <iostream>

//#include "TcpClient.h"

//#include <thread>

//void reciever_job(TcpClient* client) {
//    while (true) {
//        if (client->ready_read()) {
//            std::string response = client->receive_data();
//            if (!response.empty())
//            {
//                std::cout << "\n" << response << std::flush;
//            }
//        }
//    }
//}


//int main()
//{
//    TcpClient client;

//    std::string server_ip = "127.0.0.1"; // Server address
//    int server_port = 8080;              // Server port

//    if (!client.connect_to_server(server_port, server_ip))
//    {
//        std::cerr << "Failed to connect to server!" << std::endl;
//        return 1;
//    }

//    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;

//    // Receive response from server
//    std::thread recv_thread(reciever_job, &client);

//    while (true) {
//        std::string msg;
//        std::getline(std::cin, msg);

//        if (!msg.empty())
//        {
//            if (!client.send_data(msg))
//            {
//                std::cerr << "Failed to send data!" << std::endl;
//                return 1;
//            }
//        }
//    }

//    recv_thread.join();

//    client.close_connection();
//    std::cout << "Client disconnected." << std::endl;

//    return 0;
//}


#include "TicTacToe_Client.h"

int main()
{
    std::string ip = "127.0.0.1"; // Server address
    int port = 8080;              // Server port

    TTT_Player *player = new TTT_Player(port, ip);
    player->enter_game();

    return 0;
}
