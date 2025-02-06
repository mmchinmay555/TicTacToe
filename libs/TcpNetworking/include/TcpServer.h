#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "Socket.h"
#include <memory>

class TcpServer
{
private:
    /* Tcp Server socket */
    std::unique_ptr<Socket> server_socket;
    int port;

public:
    /* Constructor: Creates a TCP server socket */
    TcpServer(int port);

    /* Start the server (bind & listen) */
    bool start();

    /* Check if there are pending connections */
    bool has_pending_connections();

    /* Accpet a client connection, returns a Socket object */
    std::unique_ptr<Socket> accept_client();

    /* Close the server */
    void close_server();

    /* Return port */
    int get_port();
};

#endif // TCPSERVER_H
