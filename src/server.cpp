#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <vector>

// Function to handle each client's connection
void handleClient(sf::TcpSocket* client)
{
    char data[100];
    std::size_t received;

    while (true)
    {
        // Receive data from the client
        if (client->receive(data, sizeof(data), received) != sf::Socket::Done)
        {
            std::cerr << "Error receiving data from client or client disconnected" << std::endl;
            break;
        }

        // Echo the received data back to the client
        std::cout << "Received: " << std::string(data, received) << std::endl;
        if (client->send(data, received) != sf::Socket::Done)
        {
            std::cerr << "Error sending data to client" << std::endl;
            break;
        }
    }

    // Clean up the client socket after the client disconnects
    delete client;
}

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

    // Vector to keep track of client threads
    std::vector<std::thread> clientThreads;

    while (true)
    {
        // Accept a new connection
        sf::TcpSocket* client = new sf::TcpSocket;
        if (listener.accept(*client) != sf::Socket::Done)
        {
            std::cerr << "Error accepting new connection" << std::endl;
            delete client;
            continue;
        }
        std::cout << "Client connected: " << client->getRemoteAddress() << std::endl;

        // Start a new thread to handle the client
        clientThreads.emplace_back(handleClient, client);
    }

    // Join all client threads before exiting (although this point is never reached in this example)
    for (auto& thread : clientThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    return 0;
}
