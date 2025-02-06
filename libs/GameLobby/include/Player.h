#ifndef PLAYER_H
#define PLAYER_H

#include <Socket.h>
#include <memory>

class Player
{
private:
    /* Player ID (assigned by the server) */
    int id;

    /* Socket through which the communication with server happens */
    std::unique_ptr<Socket> socket;

    /* ID of the player's opponent */
    int opponent_id;

    /* Whether it's player's turn */
    bool is_allowed_to_play;

public:
    /* Default constructor */
    Player();

    /* Constructor */
    Player(int id, std::unique_ptr<Socket> socket);

    /* Move constructor */
    Player& operator=(Player&& other);

    /* Returns ID */
    int get_id();

    /* Returns Opponent ID */
    int get_opponent_id();

    /* Sets opponent ID */
    void set_opponent_id(int id);

    /* Sends data to the server, throught the socket */
    bool send_data(const std::string &data);

    /* Checks for any unread data in the socket*/
    bool ready_read();

    /* Reads data from the socket */
    std::string read_data();

    /* Modifiers for is_allowed_to_play */
    bool get_is_allowed_to_play() const;
    void set_is_allowed_to_play(bool newIs_allowed_to_play);
};

#endif // PLAYER_H
