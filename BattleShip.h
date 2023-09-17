#include <string>
#include <SFML/Graphics.hpp>

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

class BattleShip {
    public:
    sf::Color color;
    sf::Vector2i coords;
    bool fixed;
    int index;
    int length;
    int width;
    int height;
    sf::RectangleShape* shape ;
    int offset;
    std::string direction= "vertical";
    BattleShip(int _length, int index);
    BattleShip& rotate();
    BattleShip& reset();
    BattleShip& setColor(sf::Color);
    BattleShip& setPos(sf::Vector2f);
    BattleShip& setCoords(sf::Vector2i);
    
    bool canDrop();
};
#endif