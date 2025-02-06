cmake_minimum_required(VERSION 3.14)
project(TicTacToe)

add_library(TicTacToe
    src/TicTacToe_Server.cpp
    src/TicTacToe_Client.cpp
)

target_include_directories(TicTacToe PUBLIC include Threads::Threads)

# Link against GameLobby
target_link_libraries(TicTacToe PUBLIC GameLobby)
