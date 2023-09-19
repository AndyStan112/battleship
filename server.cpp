
#include <iostream>
#include <SFML/Network.hpp>
#include <Array>

int main()
{
    std::vector<sf::TcpSocket *> clients;
    std::vector<std::pair<sf::TcpSocket, sf::TcpSocket>> games;
    sf::TcpListener listener;
    int highestId = 0;
    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cout << "bind error";
    }

    // accept a new connection

    while (true)
    {

        sf::SocketSelector selector;
        selector.add(listener);

        for (auto client : clients)
        {
            selector.add(*client);
        }

        if (selector.wait())
        {
            if (selector.isReady(listener))
            {

                // New client is trying to connect
                sf::TcpSocket *newClient = new sf::TcpSocket;
                if (listener.accept(*newClient) == sf::Socket::Done)
                {
                    std::cout << "pushing back\n";
                    clients.push_back(newClient);
                }
            }
            else
            {
                // Handle data from existing clients
                for (auto client : clients)
                {

                    if (selector.isReady(*client))
                    {

                        sf::Packet clientPacket;
                        sf::Packet serverPacket;
                        std::string message = "test";
                        if (client->receive(clientPacket) == sf::Socket::Done)
                        {
                            int id;
                            clientPacket >> id;
                            std::cout << "server got a client";
                            if (id == -1)
                            {
                                serverPacket << highestId++;
                                client->send(serverPacket);
                            }
                            else
                                std::cout << "not";
                        }
                    }
                }
            }
        }

        // serverPacket << test;
        // client.send(serverPacket);
        //  std::cout << "hello World";
    }

    return 0;
}