#include <SFML/Graphics.hpp>
#include "../constants/constants.h"
#include "../grid/GameTile.h"
#include "../shapes/RoundedRectangle.cpp"

GameTile::GameTile(int i, int j, int offset, sf::Color color, sf::Vector2i _margin)
{
    margin = _margin;
    pos.x = GRID_CELL_SIZE * i + margin.x + GRID_CELL_THICKNESS * i; 
    pos.y = GRID_CELL_SIZE * j + margin.y + GRID_CELL_THICKNESS * j;

    // offset the enemy grid
    pos.x += offset;
    
    shape->setFillColor(color);
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