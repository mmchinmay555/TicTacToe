#include "socket.h"

Socket::Socket(int domain, int type, int protocol)
    : is_valid(false)
    , sockfd(socket(domain, type, protocol))
{
    if (sockfd == -1) {
        perror("Socket creation failed");
    } else {
        is_valid = true;
    }
}

Socket::Socket(int existing_fd)
    : sockfd(existing_fd)
    , is_valid(true)
{

}

bool Socket::bind_socket(int port, const std::string &ip)
{
    if (!is_valid) return false;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0) {
        perror("Invalid IP address");
        return false;
    }

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("Bind failed");
        return false;
    }

    return true;
}

bool Socket::connect_socket(int port, const std::string& ip)
{
    if (!is_valid) return false;

    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &address.sin_addr) <= 0) {
        perror("Invalid address");
        return false;
    }

    if (connect(sockfd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        perror("Connection failed");
        return false;
    }

    return true;
}

void Socket::close_socket()
{
    if (is_valid) {
        shutdown(sockfd, SHUT_RDWR);
        close(sockfd);

        is_valid = false;
    }
}

int Socket::get_socket_fd() const
{
    return sockfd;
}

bool Socket::is_valid_socket()
{
    return is_valid;
}

std::string Socket::get_peer_name()
{
    if (!is_valid) return "";

    struct sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(peer_addr);
    if (getpeername(sockfd, (struct sockaddr*)&peer_addr, &addr_len) == -1) {
        perror("getpeername failed");
        return "";
    }
    return inet_ntoa(peer_addr.sin_addr) + std::string(":") + std::to_string(ntohs(peer_addr.sin_port));
}

bool Socket::send_data(const std::string &data)
{
    if (!is_valid) return false;

    uint32_t size = htonl(data.size()); // Convert to network byte order
    ssize_t bytes_sent = send(sockfd, &size, sizeof(size), 0);
    if (bytes_sent == -1) return false;

    bytes_sent = send(sockfd, data.c_str(), data.length(), 0);
    return bytes_sent != -1;
}

bool Socket::ready_read()
{
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);

    struct timeval timeout = {0, 0}; // Non-blocking
    int result = select(sockfd + 1, &read_fds, nullptr, nullptr, &timeout);
    return result > 0 && FD_ISSET(sockfd, &read_fds);
}

std::string Socket::read_data()
{
    if (!is_valid_socket()) return "";

    uint32_t size;
    ssize_t bytes_received = recv(sockfd, &size, sizeof(size), 0);

    std::string data;

    if (bytes_received <= 0) return "";

    size = ntohl(size); // Convert from network byte order

    char buffer[size]; // Dynamic allocation (consider heap allocation for safety)
    bytes_received = recv(sockfd, buffer, size, 0);

    if (bytes_received <= 0) return "";

    data.assign(buffer, bytes_received);
    return data;
}

Socket::~Socket()
{
    close_socket();
}
