#include <string>
#include <SFML/Graphics.hpp>

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

class BattleShip {
    public:
    sf::Color color;
    int length;
    int width;
    int height;
    sf::RectangleShape* shape ;
    int offset;
    std::string direction= "vertical";
    BattleShip(int _length, int index);
    BattleShip& rotate();
};
#endif