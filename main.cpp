#include <SFML/Graphics.hpp>
#include <Array>
#include <iostream>
#include <string>
#include <algorithm>
#include "battleship.cpp"
#include "constants.h"
#include "display.cpp"

class GameTile {
public:
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE));
    sf::Vector2f pos;
    GameTile(int i, int j, int offset, sf::Color color) {
        pos.x = GRID_CELL_SIZE * i + offset;
        pos.y = GRID_CELL_SIZE * j;
        shape->setFillColor(color);
        shape->setOutlineThickness(GRID_CELL_THICKNESS);
        shape->setPosition(pos.x, pos.y);
    }
};


class GameGrid {
public:
    std::array<std::array<GameTile*, 10>, 10> grid;
    std::string user;

    GameGrid(std::string _user, Display* display) {
        user = _user;

        for (int i = 0; i < TABLE_ROWS; i++) {
            for (int j = 0; j < TABLE_COLUMNS; j++) {
                if(user == "user") grid[i][j] = new GameTile(i, j, 0, sf::Color::Cyan);
                if(user == "enemy") grid[i][j] = new GameTile(i, j, display->width - (GRID_CELL_SIZE * TABLE_COLUMNS + TABLE_COLUMNS * 2 * GRID_CELL_THICKNESS), sf::Color::Black);
            }
        }
    }

    /**
     * @return `sf::Vector2f`- the distance (in pixels) of the closest grid cell to the ship, measured from the origin.
    */
    sf::Vector2f getClosestGridCellPosition(sf::Vector2f coords, BattleShip* ship) {
        sf::Vector2i closestCoords = getClosestGridCellCoordinates(coords, ship);
        return grid[closestCoords.x][closestCoords.y]->pos;
    }

    /**
     * @return `sf::Vector2i`- a pair of integers between [0, TABLE_ROWS) representing the row and column of the closest grid cell from the ship
    */
    sf::Vector2i getClosestGridCellCoordinates(sf::Vector2f coords, BattleShip* ship) {
        int i = int(coords.x) / GRID_CELL_SIZE;
        int j = int(coords.y) / GRID_CELL_SIZE;

        i = std::max(0, std::min(TABLE_ROWS - 1, i));
        j = std::max(0, std::min(TABLE_ROWS - 1, j));

        return sf::Vector2i(i, j);
    }

    bool isOutside(sf::Vector2f pos) {
        return pos.x >= GRID_CELL_SIZE * TABLE_ROWS || pos.y >= GRID_CELL_SIZE * TABLE_COLUMNS;
    }
};



int main()
{
    Display* display = new Display(DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT);

    sf::RenderWindow window(sf::VideoMode(display->width, display->height), "SFML works!");
    GameGrid userGrid = GameGrid("user", display);
    GameGrid enemyGrid = GameGrid("enemy", display);

    std::array<BattleShip*, 7> userShips = {
        new BattleShip(5,0, display),
        new BattleShip(4,1, display),
        new BattleShip(3,2, display),
        new BattleShip(2,3, display),
        new BattleShip(2,4, display),
        new BattleShip(1,5, display),
        new BattleShip(1,6, display)
    };

    BattleShip* selectedShip = NULL;
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePosition);

        // handle all input events from user
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // if the user is allowed drop a ship
                if (selectedShip && selectedShip->canDrop()) {
                    // make the cursor visible (exit "drag&drop" feel)
                    window.setMouseCursorVisible(true);

                    // if the ship is outside the board
                    if (userGrid.isOutside(mouseCoords))
                        // place the ship back in the "selection list"
                        selectedShip->reset();
                    else
                        // otherwise place the ship on the board
                        selectedShip->fixed = true;

                    selectedShip = NULL;
                }

                // if the user clicked inside the window and doesn't hold a ship
                else
                    for (auto ship : userShips)
                        // check if he is trying to grab a ship from the "selection list"
                        if (ship->shape->getGlobalBounds().contains(mouseCoords))
                        {
                            // make the cursor invisible (create a "drag&drop" feel)
                            window.setMouseCursorVisible(false);

                            selectedShip = ship;
                            break;
                        }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R && selectedShip)
                    selectedShip->rotate();
                if (event.key.code == sf::Keyboard::Q)
                    window.close();
            }
        }


        if (selectedShip) {

            // if the user holds a ship, but is outside the board
            if (userGrid.isOutside(mouseCoords)) {
                // make the ship follow the cursor (disable the snapping feel) and change the color to red 
                selectedShip->setPos(mouseCoords).setCoords(sf::Vector2i(0, 0)).setColor(sf::Color::Red);
            }

            // if the user holds a ship and is inside the board
            else {
                auto snappedShipPosition = userGrid.getClosestGridCellPosition(mouseCoords, selectedShip);
                auto snappedShipCoordinates = userGrid.getClosestGridCellCoordinates(mouseCoords, selectedShip);

                // snap the ship to the closest grid cell 
                selectedShip->setPos(snappedShipPosition).setCoords(snappedShipCoordinates);

                if (selectedShip->canDrop())
                    selectedShip->setColor(sf::Color::Green);
                else
                    selectedShip->setColor(sf::Color::Red);
            }
        }

        window.clear();
        //draw
        for (auto row : userGrid.grid) {
            for (auto tile : row) {
                window.draw(*tile->shape);
            }
        }
        for (auto row : enemyGrid.grid) {
            for (auto tile : row) {
                window.draw(*tile->shape);
            }
        }
        for (auto ship : userShips) {
            window.draw(*ship->shape);
        }
        window.display();
    }

    return 0;
}