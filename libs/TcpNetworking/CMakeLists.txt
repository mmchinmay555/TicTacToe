# TcpNetworking/CMakeLists.txt
set(TCPNETWORKING_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TCPNETWORKING_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Create a library for TcpNetworking
add_library(TcpNetworking STATIC
    ${TCPNETWORKING_SRC_DIR}/TcpServer.cpp
    ${TCPNETWORKING_SRC_DIR}/TcpClient.cpp
    ${TCPNETWORKING_SRC_DIR}/Socket.cpp
)

# Include directories
target_include_directories(TcpNetworking PUBLIC ${TCPNETWORKING_INCLUDE_DIR})

