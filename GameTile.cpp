#include <SFML/Graphics.hpp>
#include "constants.h"
#include "GameTile.h"

GameTile::GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin) {
    margin = _margin;
    pos.x = GRID_CELL_SIZE * i + offset +margin.x;
    pos.y = GRID_CELL_SIZE * j + margin.y;  
    shape->setFillColor(color);
    shape->setOutlineThickness(GRID_CELL_THICKNESS);
    shape->setPosition(pos.x, pos.y);
};