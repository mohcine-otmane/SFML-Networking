#include <SFML/Network.hpp>
#include <iostream>
#include <string>

int main()
{
    // Define server address and port
    std::string serverIp = "127.0.0.1"; // Change to server's IP if needed
    unsigned short serverPort = 5500;

    // Create a TCP socket
    sf::TcpSocket socket;

    // Connect to the server
    sf::Socket::Status status = socket.connect(serverIp, serverPort, sf::seconds(5));
    if (status != sf::Socket::Done)
    {
        std::cerr << "Error: Could not connect to server at " << serverIp << ":" << serverPort << std::endl;
        return 1;
    }

    std::cout << "Connected to server " << serverIp << ":" << serverPort << std::endl;

    // Set the socket to non-blocking (optional)
    // socket.setBlocking(false);

    // Send a message to the server
    std::string message = "Hello, Server!";
    sf::Packet packet;
    packet << message;
    if (socket.send(packet) != sf::Socket::Done)
    {
        std::cerr << "Error: Failed to send message to server." << std::endl;
        return 1;
    }

    std::cout << "Sent: " << message << std::endl;

    // Wait for the server's response
    sf::Packet receivedPacket;
    status = socket.receive(receivedPacket);

    if (status == sf::Socket::Done)
    {
        std::string receivedMessage;
        receivedPacket >> receivedMessage;
        std::cout << "Received from server: " << receivedMessage << std::endl;
    }
    else if (status == sf::Socket::Disconnected)
    {
        std::cout << "Disconnected from server." << std::endl;
    }
    else
    {
        std::cout << "No response from server." << std::endl;
    }

    return 0;
}
