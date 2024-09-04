# SFML Networking Project

This project demonstrates a simple networking application using SFML. The project includes a server and a client, each implemented as separate executables. The server listens for incoming connections, while the client connects to the server and exchanges data.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- **CMake** 3.10 or higher
- **C++ Compiler** (GCC, Clang, MSVC, etc.)
- **Git**

### Build Steps

1. Clone the repository:
    ```bash
    git clone https://github.com/mohcine-otmane/SFML-Networking.git
    cd SFML-Networking
    ```

2. Generate the build files using CMake:
    ```bash
    cmake -S . -B build
    ```

3. Build the project:
    ```bash
    cmake --build build
    ```

4. The built executables (`server` and `client`) will be located in the `build/bin` directory.

## Usage

### Running the Server

To start the server, run the following command in your terminal:
```bash
./build/bin/server
```
The server will start listening for incoming connections on a specified port.

### Running the Client

To connect to the server, run the client executable:
```bash
./build/bin/client
```
The client will connect to the server and you can start exchanging messages.

### Example Interaction

1. Start the server:
    ```bash
    ./build/bin/server
    ```

2. Run the client:
    ```bash
    ./build/bin/client
    ```

The client should successfully connect to the server, and you can observe the exchange of data between them.

## Project Structure

```
SFML-Networking/
├── CMakeLists.txt          # CMake configuration file
├── README.md               # This README file
├── src/
│   ├── server.cpp          # Server implementation
│   └── client.cpp          # Client implementation
├── build/                  # Directory where build files are generated
└── ...
```

## Contributing

Contributions are welcome! If you'd like to contribute, please fork the repository, create a feature branch, and submit a pull request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/NewFeature`)
3. Commit your Changes (`git commit -m 'Add NewFeature'`)
4. Push to the Branch (`git push origin feature/NewFeature`)
5. Open a Pull Request

## License

Distributed under The GNU General Public License v3.0. See `LICENSE` for more information.
