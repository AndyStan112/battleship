
#include <iostream>
#include <SFML/Network.hpp>
#include <Array>
#include "constants.h"
#include "util.cpp"

class User
{
public:
    std::string id;
    TileState userGrid[10][10];
    User(std::string id)
    {
        this->id = id;
    }
    void setGrid(TileState grid[10][10])
    {
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                userGrid[i][j] = grid[i][j];
    }
};

class Room
{
public:
    std::string code = get_uuid().substr(0, 6);
    User *host;
    User *enemy;
    Room(std::string id)
    {
        this->host = new User(id);
    }
    void initEnemy(std::string id)
    {
        this->enemy = new User(id);
    }
};
Room *findRoom(const std::vector<Room *> &rooms, const std::string &code)
{
    for (Room *room : rooms)
    {
        if (room->code == code)
        {
            return room;
        }
    }

    return NULL;
}
int main()
{

    std::vector<Room *> rooms;
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
                            std::string action;
                            clientPacket >> action;
                            std::string id;
                            clientPacket >> id;
                            std::cout << "server got a client\n";
                            std::cout << "server : " << action << "  " << id << '\n';
                            if (action == "create")
                            {
                                auto newRoom = new Room(id);
                                rooms.push_back(newRoom);
                                std::cout << "room : " << newRoom->code << '\n';
                                serverPacket << "ok"
                                             << "wait";
                            }
                            else if (action == "join")
                            {
                                std::string code;
                                clientPacket >> code;
                                Room *room = findRoom(rooms, code);
                                if (!room)
                                {
                                    serverPacket << "fail"
                                                 << "Room not found";
                                }
                                else
                                {
                                    room->initEnemy(id);
                                    // std::cout << "host id " << room->host->id << '\n';
                                    // std::cout << "enemy id " << room->enemy->id << '\n';
                                    serverPacket << "ok"
                                                 << "wait";
                                }

                                client->send(serverPacket);
                            }
                            else
                            {
                                serverPacket << "fail"
                                             << "unknown request";
                            }
                            client->send(serverPacket);
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