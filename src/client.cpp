#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main()
{
    // Create a socket to connect to the server
    sf::TcpSocket socket;

    // Connect to the server
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Error connecting to the server" << std::endl;
        return -1;
    }
    std::cout << "Connected to the server!" << std::endl;

    while (true)
    {
        // Read user input
        std::string message;
        std::cout << "Enter message to send to the server: ";
        std::getline(std::cin, message);

        // Send the message to the server
        if (socket.send(message.c_str(), message.size()) != sf::Socket::Done)
        {
            std::cerr << "Error sending message" << std::endl;
            continue;
        }

        // Receive response from the server
        char data[100];
        std::size_t received;
        if (socket.receive(data, sizeof(data), received) != sf::Socket::Done)
        {
            std::cerr << "Error receiving message from the server" << std::endl;
            continue;
        }

        // Display the response
        std::cout << "Server response: " << std::string(data, received) << std::endl;
    }

    return 0;
}
