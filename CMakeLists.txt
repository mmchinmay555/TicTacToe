cmake_minimum_required(VERSION 3.5)

project(GameLobby LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(TcpNetworking/)

# Add TcpNetworking's include directory
include_directories(${CMAKE_SOURCE_DIR}/TcpNetworking/include)
# Find the system threading library
find_package(Threads REQUIRED)

add_executable(
    GameLobby main.cpp
    player.h player.cpp
    gameServer.h gameServer.cpp
)

# Link GameLobby with TcpNetworking
target_link_libraries(GameLobby PRIVATE TcpNetworking Threads::Threads)

install(TARGETS GameLobby
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


