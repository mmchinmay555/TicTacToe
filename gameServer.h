#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <tcpServer.h>
#include "player.h"

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <chrono>


class GameServer
{
public:
    /* Constructor: Takes in port as an arg and initializes TcpServer object (server) */
    GameServer(int port);

    /* Destructor: Destroys the TcpServer object (server) */
    ~GameServer();

    /* Starts the server, and also opens the Lobby */
    void start_server();

    /* Closes the server */
    void close_server();

private:
    /* Monitors all the players for any messages and disconnections */
    void start_communication();

    /* Server now ready to accept new Players */
    void start_lobby();

    /* Called when new player joins or leaves the lobby */
    void match_player(int player_id);

    /* Start new session for newly matched player */
    void start_new_session(int player_1_id, int player_2_id);

    /* Called when player leaves the lobby */
    void on_player_left(int player_id);

    /* Player who doesn't have any opponent assigned yet */
    int waiting_player_id;

    /* Handle new conection */
    void handle_new_player_connection(std::unique_ptr<Socket> player_socket);

    /* Add player to the list */
    void add_player_to_map(Player& player);

    /* Forward the message to opponent */
    void forward_message_to_opponent(int player_id, const std::string& msg);

    /* Handle player disconnection */
    void handle_player_disconnection(int disconnected_player_id);

    /* Send message to player */
    void send_message_to_player(int player_id, const std::string &message);

private:
    /* The server object */
    TcpServer* server;

    /* Port number where the server is running */
    int port;

    /* List of players online */
    std::unordered_map<int, Player> players;

    /* Mutex for thread safe accessing and modifications on "players" */
    std::mutex mtx;

    /* GameServer running state */
    bool is_game_server_running;
};

#endif // GAMESERVER_H




