cmake_minimum_required(VERSION 3.14)
project(TicTacToeApp)

add_executable(TicTacToe_Game TicTacToe_Game.cpp)
add_executable(TicTacToe_Player TicTacToe_Player.cpp)

find_package(Threads REQUIRED)

# Link against TicTacToe
target_link_libraries(TicTacToe_Game PRIVATE TicTacToe)
target_link_libraries(TicTacToe_Player PRIVATE TicTacToe)

# Ensure the "executables" directory exists
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Copy the executables after building
add_custom_command(TARGET TicTacToe_Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TicTacToe_Game> ${CMAKE_BINARY_DIR}/bin/
)

add_custom_command(TARGET TicTacToe_Player POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:TicTacToe_Player> ${CMAKE_BINARY_DIR}/bin/
)
