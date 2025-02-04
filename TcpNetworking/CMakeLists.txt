cmake_minimum_required(VERSION 3.10)
project(TcpNetworking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Add source files
add_library(TcpNetworking STATIC
    src/socket.cpp
    src/tcpServer.cpp
    src/tcpClient.cpp
)

# Example programs
add_subdirectory(examples)
