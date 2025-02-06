#include "Player.h"

Player::Player()
    : id (-1)
    , socket(nullptr)
    , opponent_id(-1)
    , is_allowed_to_play(false)
{

}

Player::Player(int id, std::unique_ptr<Socket> socket)
    : id(id)
    , socket(std::move(socket))
    , opponent_id(-1)
    , is_allowed_to_play(false)
{

}

Player &Player::operator=(Player &&other)
{
    if (this != &other)
    {
        id = other.id;
        socket = std::move(other.socket);
        opponent_id = other.opponent_id;

        other.id = -1;
        other.opponent_id = -1;
    }

    return *this;
}

int Player::get_id()
{
    return id;
}

int Player::get_opponent_id()
{
    return opponent_id;
}

void Player::set_opponent_id(int id)
{
    opponent_id = id;
}

bool Player::send_data(const std::string &data)
{
    return socket->send_data(data);
}

bool Player::ready_read()
{
    return socket->ready_read();
}

std::string Player::read_data()
{
    return socket->read_data();
}

bool Player::get_is_allowed_to_play() const
{
    return is_allowed_to_play;
}

void Player::set_is_allowed_to_play(bool newIs_allowed_to_play)
{
    is_allowed_to_play = newIs_allowed_to_play;
}
