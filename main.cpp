#include <SFML/Graphics.hpp>
#include <Array>
#include <iostream>
#include <string>
#include <algorithm>
#include "constants.h"
#include "GameGrid.cpp"
#include "BattleShip.cpp"
#include "display.cpp"

int main()
{
    sf::Font font;
    if (!font.loadFromFile("fonts/FuturaBold.ttf"))
        throw "Font missing! Please download Futura Bold Font!";

    sf::Text text;

    text.setPosition(100, 100);

    text.setRotation(-90);

    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Hello world");

    // set the character size
    text.setCharacterSize(24); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    Display *display = new Display(DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT);

    sf::RenderWindow window(sf::VideoMode(display->width, display->height), "SFML works!");
    GameGrid userGrid = GameGrid("user", display);
    GameGrid enemyGrid = GameGrid("enemy", display);

    std::array<BattleShip *, 7> userShips = {
        new BattleShip(5, 0, display),
        new BattleShip(4, 1, display),
        new BattleShip(3, 2, display),
        new BattleShip(2, 3, display),
        new BattleShip(2, 4, display),
        new BattleShip(1, 5, display),
        new BattleShip(1, 6, display)};

    BattleShip *selectedShip = NULL;
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mouseCoords = window.mapPixelToCoords(mousePosition);

        // handle all input events from user
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // if the user is allowed drop a ship
                if (selectedShip)
                {

                    if (selectedShip->canDrop(userShips))
                    {
                        // make the cursor visible (exit "drag&drop" feel)
                        window.setMouseCursorVisible(true);

                        // if the ship is outside the board
                        if (userGrid.isOutside(mouseCoords))
                            // place the ship back in the "selection list"
                            selectedShip->reset();
                        else
                        {
                            selectedShip->setColor(BATTLESHIP_PLACED);
                            userGrid.setPipCells(selectedShip, true);
                        }

                        selectedShip = NULL;
                    }
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
                            userGrid.setPipCells(selectedShip, false);
                            break;
                        }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::R && selectedShip)
                    selectedShip->rotate();
                if (event.key.code == sf::Keyboard::Q)
                    window.close();
            }
        }

        if (selectedShip)
        {

            // if the user holds a ship, but is outside the board
            if (userGrid.isOutside(mouseCoords))
            {
                // make the ship follow the cursor (disable the snapping feel) and change the color to red
                selectedShip->setPos(mouseCoords).setCoords(sf::Vector2i(0, 0)).setColor(BATTLESHIP_IMPLACABLE);
            }

            // if the user holds a ship and is inside the board
            else
            {
                auto snappedShipPosition = userGrid.getClosestGridCellPosition(mouseCoords, selectedShip);
                auto snappedShipCoordinates = userGrid.getClosestGridCellCoordinates(mouseCoords, selectedShip);

                // snap the ship to the closest grid cell
                selectedShip->setPos(snappedShipPosition).setCoords(snappedShipCoordinates);

                if (selectedShip->canDrop(userShips))
                    selectedShip->setColor(BATTLESHIP_PLACABLE);
                else
                    selectedShip->setColor(BATTLESHIP_IMPLACABLE);
            }
        }

        window.clear(sf::Color::White);
        // draw
        for (auto row : userGrid.grid)
        {
            for (auto tile : row)
            {
                window.draw(*tile->shape);
                if (tile->showPip)
                    window.draw(*tile->pip);
            }
        }
        for (auto row : enemyGrid.grid)
        {
            for (auto tile : row)
            {
                window.draw(*tile->shape);
            }
        }
        for (auto ship : userShips)
        {
            window.draw(*ship->phantom);
            window.draw(*ship->shape);
        }

        // the last selected ships should be rendered above
        if (selectedShip)
            window.draw(*selectedShip->shape);

        window.draw(text);

        window.display();
    }

    return 0;
}