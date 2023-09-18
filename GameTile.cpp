#include <SFML/Graphics.hpp>
#include "constants.h"
#include "GameTile.h"

GameTile::GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin)
{
    margin = _margin;
    pos.x = GRID_CELL_SIZE * i + offset + margin.x;
    pos.y = GRID_CELL_SIZE * j + margin.y;
    shape->setFillColor(color);
    shape->setOutlineThickness(GRID_CELL_THICKNESS);
    shape->setPosition(pos.x, pos.y);
    pip->setFillColor(sf::Color::Black);
    pip->setOutlineThickness(GRID_CELL_THICKNESS / 3);
    pip->setPosition(pos.x + GRID_CELL_SIZE / 4, pos.y + GRID_CELL_SIZE / 4);
};
GameTile &GameTile::setShowPip(bool show)
{
    showPip = show;
    return *this;
};