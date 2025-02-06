#ifndef TTT_SERVER_H
#define TTT_SERVER_H

#include "GameServer.h"

#include <utility>

struct pair_hash
{
    std::size_t operator()(const std::pair<int, int>& p) const
    {
        return (std::hash<int>()(p.first)) ^ (std::hash<int>()(p.second) << 1);
    }
};

/* Mayer's Singleton (Thread safe) */
class TTT_Server : public GameServer
{
private:
    TTT_Server(int port);

public:
    static TTT_Server* get_instance(int port);

    TTT_Server(TTT_Server& other) = delete;
    TTT_Server& operator=(TTT_Server& other) = delete;

// GameServer interface
protected:
    virtual void game_started(int player1_id, int player2_id);
    virtual void game_ended(int player1_id, int player2_id);

    virtual void handle_player_move(int player_id, const std::string &msg);
    virtual int update_move_and_get_reply(int player_id, const std::string &msg, std::string &reply);

private:
    std::pair<int, int> create_pair(int player1_id, int player2_id);

    std::unordered_map<int, std::pair<int, int>> player_to_pair_map;
    std::unordered_map<std::pair<int, int>, std::array<int, 9>, pair_hash> players_to_session_map;
};

#endif // TTT_SERVER_H
