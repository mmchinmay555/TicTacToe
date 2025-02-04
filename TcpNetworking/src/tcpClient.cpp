#include "tcpClient.h"

TcpClient::TcpClient()
    : client_socket(std::make_unique<Socket>(AF_INET, SOCK_STREAM, 0))
{

}

bool TcpClient::connect_to_server(int port, const std::string &ip)
{
    return client_socket->connect_socket(port, ip);
}

bool TcpClient::send_data(const std::string &data)
{
    return client_socket->send_data(data);
}

bool TcpClient::ready_read()
{
    return client_socket->ready_read();
}

std::string TcpClient::receive_data()
{
    return client_socket->read_data();
}

void TcpClient::close_connection()
{
    return client_socket->close_socket();
}
