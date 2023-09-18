#include <SFML/Graphics.hpp>
#include "BattleShip.h"
#include "constants.h"
#include "GameGrid.h"
#include "GameTile.cpp"

GameGrid::GameGrid(std::string _user, Display* display) {
        user = _user;

        for (int i = 0; i < TABLE_ROWS; i++) {
            for (int j = 0; j < TABLE_COLUMNS; j++) {
                if(user == "user") grid[i][j] = new GameTile(i, j, 0, sf::Color::Cyan);
                if(user == "enemy") grid[i][j] = new GameTile(i, j, display->width - GRID_CELL_SIZE * TABLE_COLUMNS, sf::Color::Black);
            }
        }
    }

/**
 * @return `sf::Vector2f`- the distance (in pixels) of the closest grid cell to the ship, measured from the origin.
*/
sf::Vector2f GameGrid::getClosestGridCellPosition(sf::Vector2f coords, BattleShip* ship) {
    sf::Vector2i closestCoords = getClosestGridCellCoordinates(coords, ship);
    return grid[closestCoords.x][closestCoords.y]->pos;
}

/**
 * @return `sf::Vector2i`- a pair of integers between [0, TABLE_ROWS) representing the row and column of the closest grid cell from the ship
*/
sf::Vector2i GameGrid::getClosestGridCellCoordinates(sf::Vector2f coords, BattleShip* ship) {
    int i = int(coords.x) / GRID_CELL_SIZE;
    int j = int(coords.y) / GRID_CELL_SIZE;

    i = std::max(0, std::min(TABLE_ROWS - 1, i));
    j = std::max(0, std::min(TABLE_ROWS - 1, j));

    return sf::Vector2i(i, j);
}

bool GameGrid::isOutside(sf::Vector2f pos) {
    return pos.x >= GRID_CELL_SIZE * TABLE_ROWS || pos.y >= GRID_CELL_SIZE * TABLE_COLUMNS;
}
