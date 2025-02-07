#include "TicTacToe_Server.h"
#include <sstream>

TTT_Server::TTT_Server(int port)
    : GameServer(port)
{

}

TTT_Server *TTT_Server::get_instance(int port)
{
    static TTT_Server* server = new TTT_Server(port);
    return server;
}

void TTT_Server::game_started(int player1_id, int player2_id)
{
    std::pair<int, int> paired_players = create_pair(player1_id, player2_id);

    if (player_to_pair_map.find(player1_id) == player_to_pair_map.end() && player_to_pair_map.find(player2_id) == player_to_pair_map.end())
    {
        // Map both players to the pair;
        player_to_pair_map[player1_id] = paired_players;
        player_to_pair_map[player2_id] = paired_players;
    }
    else
    {
        std::cerr << "SOME ERRR.. MATCHING" << std::endl;
    }

    if (players_to_session_map.find(paired_players) == players_to_session_map.end())
    {
        players_to_session_map[paired_players] = std::array<char, 9>();
        initialise_board(players_to_session_map[paired_players]);
    }
    else
    {
        std::cerr << "Trying to start the game again.." << std::endl;
    }
}

void TTT_Server::game_ended(int player1_id, int player2_id)
{
    std::pair<int, int> paired_players = create_pair(player1_id, player2_id);

    if (players_to_session_map.find(paired_players) != players_to_session_map.end())
    {
        players_to_session_map.erase(paired_players);
    }
    else
    {
        std::cerr << "Trying to end the game again.." << std::endl;
    }

    if (player_to_pair_map.find(player1_id) != player_to_pair_map.end() && player_to_pair_map.find(player2_id) != player_to_pair_map.end())
    {
        // Erase players map
        player_to_pair_map.erase(player1_id);
        player_to_pair_map.erase(player2_id);
    }
    else
    {
        std::cerr << "SOME ERRR.. MATCHING" << std::endl;
    }
}

void TTT_Server::handle_player_move(int player_id, const std::string &msg)
{
    if (std::stoi(msg) - 1 > 8) return;

    if (player_to_pair_map[player_id].first == player_id)
    {
        players_to_session_map[player_to_pair_map[player_id]][std::stoi(msg) - 1] = 'X';
    }
    else
    {
        players_to_session_map[player_to_pair_map[player_id]][std::stoi(msg) - 1] = 'O';
    }
}

int TTT_Server::update_move_and_get_reply(int player_id, const std::string &msg, std::string &reply)
{
    handle_player_move(player_id, msg);

    reply.clear();

    get_reply(player_id, reply);

    char status = check_game_status(player_id);

    if (status != 'P')
    {
        // GAME ENDED
        initialise_board(players_to_session_map[player_to_pair_map[player_id]]);

        if (status == 'N')
        {
            // 0  : No winner
            return 0;
        }

        if (status == 'X')
        {
            // player_id with lesser ID than opponent WON
            if (player_to_pair_map[player_id].first == player_id)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }

        if (player_to_pair_map[player_id].second == player_id)
        {
            return 1;
        }

        // player_id with greater ID than opponent WON
        return 2;
    }


    // -1 : Match in progress
    return -1;
}

bool TTT_Server::validate_input(int player_id, const std::string &msg)
{
    if (!(msg.size() == 1 && msg[0] >= '1' && msg[0] <= '9')) return false;

    int index_to_write = std::stoi(msg) - 1;
    std::pair<int, int> player_pair = player_to_pair_map[player_id];

    if (players_to_session_map[player_pair][index_to_write] == 'X' || players_to_session_map[player_pair][index_to_write] == 'O') return false;

    return true;
}

void TTT_Server::get_current_data(int player_id, std::string &data)
{
    get_reply(player_id, data);
}

std::pair<int, int> TTT_Server::create_pair(int player1_id, int player2_id)
{
    std::pair<int, int> players_pair;

    if (player1_id < player2_id)
    {
        players_pair = std::pair<int, int>(player1_id, player2_id);
    }
    else
    {
        players_pair = std::pair<int, int>(player2_id, player1_id);
    }

    return players_pair;
}

char TTT_Server::check_game_status(int player_id)
{
    std::pair<int, int> player_pair = player_to_pair_map[player_id];
    std::array<char, 9> board = players_to_session_map[player_pair];

    for (const auto& combo : winningCombos)
    {
        if (board[combo[0]] == board[combo[1]] && board[combo[1]] == board[combo[2]])
        {
            return board[combo[0]]; // Return the winning player ID;
        }
    }

    for (auto c : board)
    {
        if (c != 'X' && c != 'O') return 'P';
    }

    // NO WINNER
    return 'N';
}

void TTT_Server::get_reply(int player_id, std::string &reply)
{
    reply.clear();
    reply += "\n";

    std::pair<int, int> player_pair = player_to_pair_map[player_id];
    std::array<char, 9> board = players_to_session_map[player_pair];

    std::ostringstream os;
    // Print top border
    os << "+---+---+---+\n";

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
        {
            os << "|";
        }

        os << " " << board[i] << " |";

        if ((i + 1) % 3 == 0)
        {
            os << "\n";
            if (i < 6)
            { // Print row separator after first two rows
                os << "----+---+---+\n";
            }
        }
    }

    // Print bottom border
    os << "+---+---+---+";

    reply += os.str();
}

void TTT_Server::initialise_board(std::array<char, 9>& board)
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = '1' + i;
    }
}
