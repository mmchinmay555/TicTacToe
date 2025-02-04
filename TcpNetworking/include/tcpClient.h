#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "socket.h"

#include <memory>

class TcpClient
{
private:
    std::unique_ptr<Socket> client_socket;
public:
    TcpClient();

    /* Connect to a server */
    bool connect_to_server(int port, const std::string& ip = "0.0.0.0");

    /* Send data */
    bool send_data(const std::string& data);

    /* Check if data is available */
    bool ready_read();

    /* Receive data */
    std::string receive_data();

    /* Close the connection */
    void close_connection();
};

#endif // TCPCLIENT_H
