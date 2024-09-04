#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>

std::unordered_map<int, sf::TcpSocket*> clients;
sf::TcpListener listener;
int clientCounter = 0;

void handleClient(int clientId, sf::TcpSocket* clientSocket) {
    char buffer[1024];
    std::size_t received;

    while (true) {
        sf::Socket::Status status = clientSocket->receive(buffer, sizeof(buffer), received);
        if (status == sf::Socket::Done) {
            int targetClientId = buffer[0]; // Assume first byte is the target client ID
            std::string message(buffer + 1, received - 1);

            if (clients.find(targetClientId) != clients.end()) {
                clients[targetClientId]->send(message.c_str(), message.size());
            } else {
                std::cerr << "Client " << targetClientId << " not found!" << std::endl;
            }
        } else {
            std::cerr << "Client " << clientId << " disconnected" << std::endl;
            break;
        }
    }

    clientSocket->disconnect();
    delete clientSocket;
    clients.erase(clientId);
}

void acceptClients() {
    while (true) {
        sf::TcpSocket* clientSocket = new sf::TcpSocket();
        if (listener.accept(*clientSocket) == sf::Socket::Done) {
            clientCounter++;
            clients[clientCounter] = clientSocket;
            std::cout << "Client " << clientCounter << " connected." << std::endl;

            // Start a thread to handle this client
            std::thread clientThread(handleClient, clientCounter, clientSocket);
            clientThread.detach();
        } else {
            delete clientSocket;
        }
    }
}

int main() {
    if (listener.listen(54000) != sf::Socket::Done) {
        std::cerr << "Error starting server on port 54000" << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port 54000..." << std::endl;

    // Start the client acceptance loop
    acceptClients();

    return 0;
}
