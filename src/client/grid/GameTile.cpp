#include <SFML/Graphics.hpp>
#include "../constants/constants.h"
#include "../grid/GameTile.h"
#include "../shapes/RoundedRectangle.cpp"

GameTile::GameTile(int i, int j, sf::Color color)
{
    shape->setFillColor(color);

    Pip *pip = new Pip();
    children.push_back(pip);

    pip->shape->setFillColor(sf::Color::Black);
    pip->shape->setOutlineThickness(GRID_CELL_THICKNESS / 3);
};