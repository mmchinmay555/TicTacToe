# TicTacToe


## Features

- **Cross-Platform Networking**: Built using C++ for seamless communication between client and server.
- **Modular Components**: Each subproject is designed to be reusable across different projects.
- **Game Lobby**: Matchmaking functionality with turn-based gameplay.
- **Easy Setup**: Simple to integrate into your own multiplayer games.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/tictactoe-multiplayer.git
    cd tictactoe-multiplayer
    ```

2. Ensure you have **CMake** installed on your machine.

3. Create a build directory and compile the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

## Usage

1. **Run the Game Server**:
    To start the game server, use:
    ```bash
    ./TicTacToe_Server
    ```

2. **Run the Game Client**:
    To connect a client to the server, use:
    ```bash
    ./TicTacToe_Client
    ```

    Players will be matched through the **GameLobby**.

## Dependencies

- **C++17** or later.
- **CMake** for building the project.
- No external libraries are required.

## Contributing

Feel free to fork this project, submit issues, and create pull requests. Contributions are always welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Built with ❤️ by [Your Name](https://github.com/yourusername)

## Structure of the project

```
TicTacToe_Project/
│── CMakeLists.txt
│
├── scripts/                # shell scripts to start and join the game after building
│   ├── start_game.sh
│   ├── join_game.sh
│
├── libs/
│   ├── TcpNetworking/
│   │   ├── include/
│   │   ├── src/
│   │   ├── CMakeLists.txt
│   │
│   ├── GameLobby/
│   │   ├── include/
│   │   ├── src/
│   │   ├── CMakeLists.txt
│   │
│   ├── TicTacToe/
│   │   ├── include/
│   │   ├── src/
│   │   ├── CMakeLists.txt
│
├── app/
│   ├── TicTacToe_Game.cpp
│   ├── TicTacToe_Player.cpp
│   ├── CMakeLists.txt


```
