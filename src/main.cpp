#include <SFML/Network.hpp>
#include <iostream>

int main()
{
    // Create a listener to accept new connections
    sf::TcpListener listener;

    // Bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cerr << "Error binding the listener to port 53000" << std::endl;
        return -1;
    }
    std::cout << "Server is listening to port 53000, waiting for connections..." << std::endl;

    // Accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cerr << "Error accepting new connection" << std::endl;
        return -1;
    }
    std::cout << "Client connected: " << client.getRemoteAddress() << std::endl;

    // Receive and send data in a loop
    while (true)
    {
        char data[100];
        std::size_t received;

        // Receive data from the client
        if (client.receive(data, sizeof(data), received) != sf::Socket::Done)
        {
            std::cerr << "Error receiving data from client" << std::endl;
            break;
        }

        // Echo the received data back to the client
        std::cout << "Received: " << std::string(data, received) << std::endl;
        if (client.send(data, received) != sf::Socket::Done)
        {
            std::cerr << "Error sending data to client" << std::endl;
            break;
        }
    }

    return 0;
}
