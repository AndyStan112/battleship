#pragma once

#include <SFML/Graphics.hpp>
#include "BattleShip.h"
#include "constants.h"
#include "GameTile.h"

class GameGrid
{
public:
    std::array<std::array<GameTile *, 10>, 10> grid;
    std::string user;

    GameGrid(std::string _user, Display *display);

    /**
     * @return `sf::Vector2f`- the distance (in pixels) of the closest grid cell to the ship, measured from the origin.
     */
    sf::Vector2f getClosestGridCellPosition(sf::Vector2f coords, BattleShip *ship);

    /**
     * @return `sf::Vector2i`- a pair of integers between [0, TABLE_ROWS) representing the row and column of the closest grid cell from the ship
     */
    sf::Vector2i getClosestGridCellCoordinates(sf::Vector2f coords, BattleShip *ship);

    GameGrid &setPipCells(BattleShip *ship);
    bool isOutside(sf::Vector2f pos);
};
