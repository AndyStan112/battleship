#include <SFML/Graphics.hpp>
#include "constants.h"
#include "GameTile.h"

GameTile::GameTile(int i, int j, int offset, sf::Color color) {
    pos.x = GRID_CELL_SIZE * i + offset;
    pos.y = GRID_CELL_SIZE * j;
    shape->setFillColor(color);
    shape->setOutlineThickness(GRID_CELL_THICKNESS);
    shape->setPosition(pos.x, pos.y);
};