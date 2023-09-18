#include <SFML/Graphics.hpp>
#include "constants.h"
#include "GameTile.h"
#include "RoundedRectangle.cpp"

GameTile::GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin) {
    margin = _margin;
    pos.x = GRID_CELL_SIZE * i + offset +margin.x + 2 * i;
    pos.y = GRID_CELL_SIZE * j + margin.y + 2 * j;  

    shape->setFillColor(color);
    shape->setPosition(pos.x, pos.y);
};