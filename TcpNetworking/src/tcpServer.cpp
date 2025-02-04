#include "tcpServer.h"

TcpServer::TcpServer(int port)
    : server_socket(std::make_unique<Socket>(AF_INET, SOCK_STREAM, 0))
    , port(port)
{

}

bool TcpServer::start()
{
    if (!server_socket->bind_socket(port)) {
        return false;
    }

    if (listen(server_socket->get_socket_fd(), 5) == -1) {
        perror("Listen failed");
        return false;
    }
    return true;
}

bool TcpServer::has_pending_connections()
{
    // We simulate non-blocking check using select() or similar techniques
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(server_socket->get_socket_fd(), &read_fds);

    struct timeval timeout = {0, 0}; // Non-blocking

    // Check if there's a pending connection
    int result = select(server_socket->get_socket_fd() + 1, &read_fds, nullptr, nullptr, &timeout);
    return result > 0 && FD_ISSET(server_socket->get_socket_fd(), &read_fds);
}

std::unique_ptr<Socket> TcpServer::accept_client()
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int client_fd = accept(server_socket->get_socket_fd(), (struct sockaddr *)&client_addr, &addr_len);
    if (client_fd == -1) {
        perror("Accept failed");
        return nullptr;
    }

    return std::make_unique<Socket>(client_fd);
}

void TcpServer::close_server()
{
    server_socket->close_socket();
}

int TcpServer::get_port()
{
    return port;
}
