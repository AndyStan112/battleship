
#include <iostream>
#include <SFML/Network.hpp>
int main()
{
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cout << "bind error";
    }

    // accept a new connection
    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "accept error";
    }

    // use "client" to communicate with the connected client,
    // and continue to accept new connections with the listener
    sf::Packet packet;
    std::string test = "test";
    packet << test;
    client.send(packet);
    std::cout << "hello World";
    return 0;
}