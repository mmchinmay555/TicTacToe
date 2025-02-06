cmake_minimum_required(VERSION 3.10)
project(TicTacToe_Project)

# Enable C++17 standard (modify if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for libraries and main application
add_subdirectory(TcpNetworking)
add_subdirectory(GameLobby)
add_subdirectory(TicTacToe)
add_subdirectory(app)
