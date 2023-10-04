#include <SFML/Graphics.hpp>
#include "../battleship/BattleShip.h"
#include "../constants/constants.h"
#include "../grid/GameGrid.h"
#include "../grid/GameTile.cpp"

GameGrid::GameGrid(std::string _user, Display *display)
{
    user = _user;

    for (int i = 0; i < TABLE_ROWS; i++)
    {
        for (int j = 0; j < TABLE_COLUMNS; j++)
        {
            if (user == "user")
                grid[i][j] = new GameTile(i, j, WATER);
            if (user == "enemy")
                grid[i][j] = new GameTile(i, j, FOG);
        }
    }
}

/**
 * @return `sf::Vector2f`- the distance (in pixels) of the closest grid cell to the ship, measured from the origin.
 */
sf::Vector2f GameGrid::getClosestGridCellPosition(sf::Vector2f coords, BattleShip *ship)
{
    sf::Vector2i closestCoords = getClosestGridCellCoordinates(coords, ship);
    return grid[closestCoords.x][closestCoords.y]->shape->getPosition();
}

/**
 * @return `sf::Vector2i`- a pair of integers between [0, TABLE_ROWS) representing the row and column of the closest grid cell from the ship
 */
sf::Vector2i GameGrid::getClosestGridCellCoordinates(sf::Vector2f coords, BattleShip *ship)
{
    int i = int(coords.x) / (GRID_CELL_SIZE + GRID_CELL_THICKNESS);
    int j = int(coords.y) / (GRID_CELL_SIZE + GRID_CELL_THICKNESS);

    i = std::max(0, std::min(TABLE_ROWS - 1, i));
    j = std::max(0, std::min(TABLE_ROWS - 1, j));

    return sf::Vector2i(i, j);
}

bool GameGrid::isOutside(sf::Vector2f pos)
{
    return pos.x >= (GRID_CELL_SIZE + GRID_CELL_THICKNESS) * TABLE_ROWS || pos.y >= (GRID_CELL_SIZE + GRID_CELL_THICKNESS) * TABLE_COLUMNS;
}

GameGrid &GameGrid::setPipCells(BattleShip *ship, bool show)
{
    int i = ship->coords.x;
    int j = ship->coords.y;
    if (ship->direction == "horizontal")
        for (int k = 0; k < ship->length; k++) {
            Pip* pip = grid[i + k][j]->children[0];
            pip->showPip = true;
        }
    else
        for (int k = 0; k < ship->length; k++) {
            Pip* pip = grid[i][j + k]->children[0];
            pip->showPip = true;
        }

    return *this;
}