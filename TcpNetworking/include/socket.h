#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#include <cstring>     // memset
#include <unistd.h>    // close()
#include <arpa/inet.h> // socket functions

class Socket
{
protected:
    int sockfd;
    struct sockaddr_in address;
    bool is_valid;

public:
    /* Constructor: Creates the socket */
    Socket(int domain, int type, int protocol);

    /* Constructor: Creates socket from existing file descriptor */
    explicit Socket(int existing_fd);

    /* Bind the socket to an IP and port (For Server) */
    bool bind_socket(int port, const std::string& ip = "0.0.0.0");

    /* Connect the socket to a remote server (For Client) */
    bool connect_socket(int port, const std::string& ip = "0.0.0.0");

    /* Close socket */
    void close_socket();

    /* Return socket file descriptor */
    int get_socket_fd() const;

    /* Return status of socket validity */
    bool is_valid_socket();

    /* Retrieve the IP address and port of the connected peer (client) */
    std::string get_peer_name();

    /* Send data to a client */
    bool send_data(const std::string &data);

    /* Returns TRUE if unread-data exists */
    bool ready_read();

    /* Receive data from a client */
    std::string read_data();

    /* Destructor: Ensures socket is closed */
    ~Socket();
};

#endif // SOCKET_H
