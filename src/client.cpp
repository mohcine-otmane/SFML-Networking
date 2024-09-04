#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpSocket socket;
    if (socket.connect("127.0.0.1", 54000) != sf::Socket::Done) {
        std::cerr << "Error connecting to the server" << std::endl;
        return 1;
    }

    std::cout << "Connected to the server" << std::endl;

    std::string input;
    char buffer[1024];
    std::size_t received;

    while (true) {
        std::cout << "Enter the target client ID: ";
        int targetClientId;
        std::cin >> targetClientId;
        std::cin.ignore();  // To clear the newline character from the input buffer

        std::cout << "Enter your message: ";
        std::getline(std::cin, input);

        buffer[0] = static_cast<char>(targetClientId);  // The first byte is the target client ID
        std::copy(input.begin(), input.end(), buffer + 1);

        if (socket.send(buffer, input.size() + 1) != sf::Socket::Done) {
            std::cerr << "Error sending message" << std::endl;
            break;
        }

        if (socket.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
            std::cout << "Received message: " << std::string(buffer, received) << std::endl;
        }
    }

    return 0;
}
