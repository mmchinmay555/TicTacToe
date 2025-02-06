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

# Copy the shell scripts to the build directory after building
file(COPY scripts/start_game.sh DESTINATION ${CMAKE_BINARY_DIR})
file(COPY scripts/join_game.sh DESTINATION ${CMAKE_BINARY_DIR})

# Make the scripts executable
execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/start_game.sh)
execute_process(COMMAND chmod +x ${CMAKE_BINARY_DIR}/join_game.sh)
