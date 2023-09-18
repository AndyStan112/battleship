#pragma once

#include <SFML/Graphics.hpp>
#include "constants.h"

class GameTile {
public:
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
    sf::Vector2f pos;
    GameTile(int i, int j, int offset, sf::Color color);
};
