#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "display.h"

class GameGrid;

class BattleShip
{
public:
    sf::Color color;
    sf::Vector2i coords;
    Display *display;
    bool fixed;
    int index;
    int length;
    int width;
    int height;
    sf::RectangleShape *shape;
    sf::RectangleShape *phantom;
    int offset;
    std::string direction = "vertical";
    BattleShip(int _length, int _index, Display *_displayHeight);
    BattleShip &rotate();
    BattleShip &reset();
    BattleShip &setColor(sf::Color);
    BattleShip &setPos(sf::Vector2f);
    BattleShip &setCoords(sf::Vector2i);
    BattleShip &setDefaultState();
    bool canDrop(std::array<BattleShip *, 7> ships);
};