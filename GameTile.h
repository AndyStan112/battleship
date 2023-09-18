#pragma once

#include <SFML/Graphics.hpp>
#include "constants.h"

class GameTile
{
public:
    sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
    sf::CircleShape *pip = new sf::CircleShape(GRID_CELL_SIZE / 4);
    bool showPip = false;
    sf::Vector2f pos;
    sf::Vector2i margin;
    GameTile &setShowPip(bool show);
    GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin);
};
