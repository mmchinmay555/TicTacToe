# GameLobby/CMakeLists.txt
set(GAMELOBBY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GAMELOBBY_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create a library for GameLobby
add_library(GameLobby STATIC
    ${GAMELOBBY_SRC_DIR}/GameServer.cpp
    ${GAMELOBBY_SRC_DIR}/Player.cpp
)

# Find the system threading library
find_package(Threads REQUIRED)

# Link TcpNetworking library
target_link_libraries(GameLobby PUBLIC TcpNetworking Threads::Threads)

# Include directories
target_include_directories(GameLobby PUBLIC ${GAMELOBBY_INCLUDE_DIR})
