# TicTacToe
```
TicTacToe_Project/
│── CMakeLists.txt  
│
├── TcpNetworking/
│   ├── include/
│   ├── src/
│   ├── CMakeLists.txt
│
├── GameLobby/
│   ├── include/
│   │   ├── GameServer.h  # <== This must be found by TicTacToe_Server.h
│   ├── src/
│   ├── CMakeLists.txt
│
├── TicTacToe/
│   ├── include/
│   │   ├── TicTacToe_Server.h  # Uses GameServer.h
│   │   ├── TicTacToe_Client.h
│   ├── src/
│   ├── CMakeLists.txt
│
├── app/
│   ├── TicTacToe_Game.cpp
│   ├── TicTacToe_Player.cpp
│   ├── CMakeLists.txt

```
