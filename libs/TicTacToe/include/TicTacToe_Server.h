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

    // Winning combinations
    const int winningCombos[8][3] =
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };

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

    virtual bool validate_input(int player_id, const std::string &msg);
    virtual void get_current_data(int player_id, std::string &data);

private:
    std::pair<int, int> create_pair(int player1_id, int player2_id);

    std::unordered_map<int, std::pair<int, int>> player_to_pair_map;
    std::unordered_map<std::pair<int, int>, std::array<char, 9>, pair_hash> players_to_session_map;

    char check_game_status(int player_id);
    void get_reply(int player_id, std::string &reply);

    void initialise_board(std::array<char, 9>& board);
};

#endif // TTT_SERVER_H
