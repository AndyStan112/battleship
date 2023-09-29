#pragma once

#include <SFML/Graphics.hpp>
#include "../constants/constants.h"
#include "../shapes/RoundedRectangle.h"

class GameTile
{
public:
    sf::RoundedRectangleShape* shape = new sf::RoundedRectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE), 4, 10);
    sf::CircleShape *pip = new sf::CircleShape(GRID_CELL_SIZE / 4);
    bool showPip = false;
    sf::Vector2f pos;
    sf::Vector2i margin;
    GameTile &setShowPip(bool show);
    GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin);
};
