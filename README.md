# TicTacToe
TicTacToe_Project/
│── CMakeLists.txt  # Root CMake file (manages subprojects)
│
├── TcpNetworking/   # Subproject: Handles networking
│   ├── include/
│   │   ├── TcpServer.h
│   │   ├── TcpClient.h
│   │   ├── Socket.h
│   ├── src/
│   │   ├── TcpServer.cpp
│   │   ├── TcpClient.cpp
│   │   ├── Socket.cpp
│   ├── CMakeLists.txt
│
├── GameLobby/       # Subproject: Handles matchmaking
│   ├── include/
│   │   ├── GameServer.h   # Uses TcpServer
│   │   ├── Player.h
│   ├── src/
│   │   ├── GameServer.cpp
│   │   ├── Player.cpp
│   ├── CMakeLists.txt
│
├── TicTacToe/       # Main game project
│   ├── include/
│   │   ├── TicTacToe_Server.h  # Inherits from GameServer
│   │   ├── TicTacToe_Client.h  # Acts as Player
│   ├── src/
│   │   ├── TicTacToe_Server.cpp
│   │   ├── TicTacToe_Client.cpp
│   ├── CMakeLists.txt
│
├── bin/             # Stores compiled binaries
│
├── build/           # Temporary CMake build files
│
└── executables      # Final built executables
    ├── Tic_Tac_Toe_server
    ├── Tic_Tac_Toe_client
