cmake_minimum_required(VERSION 3.10)
project(TicTacToe_Project)

# Enable C++17 standard (modify if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for libraries 
add_subdirectory(libs/TcpNetworking)
add_subdirectory(libs/GameLobby)
add_subdirectory(libs/TicTacToe)

# Add subdirectory for main app
add_subdirectory(app)


