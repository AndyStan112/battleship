#include "BattleShip.h"
#include "constants.h"
#include "display.h"
#include "GameGrid.h"

BattleShip& BattleShip::setDefaultState () {
    color = sf::Color::Green;
    coords = sf::Vector2i(0, 0);
    fixed = false;
    height = GRID_CELL_SIZE * length - 4 * GRID_CELL_THICKNESS;
    width = GRID_CELL_SIZE - 4 * GRID_CELL_THICKNESS;
    offset = GRID_CELL_SIZE * index;

    shape = new sf::RectangleShape(sf::Vector2f(width, height));
    shape->setFillColor(color);
    shape->setOutlineThickness(1);

    // we subtract the ship `height` from the `display height` so all ships are aligned at the bottom of the screen
    shape->setPosition(GLOBAL_MARGIN+ offset ,display->height - height-GLOBAL_MARGIN);

    return *this;
};

BattleShip::BattleShip(int _length, int _index, Display* _display) {
    index = _index;
    length = _length;
    display = _display;

    BattleShip::setDefaultState();
};

BattleShip& BattleShip::rotate() {
    if (direction == "vertical") {
        direction = "horizontal";
        std::swap(width, height);
        shape->setSize(sf::Vector2f(width, height));
    }
    else {
        direction = "vertical";
        std::swap(width, height);
        shape->setSize(sf::Vector2f(width, height));
    }
    return *this;
};
BattleShip& BattleShip::reset() {
    BattleShip::setDefaultState();
};
BattleShip& BattleShip::setColor(sf::Color _color) {
    color = _color;
    shape->setFillColor(color);
    return *this;
};
BattleShip& BattleShip::setPos(sf::Vector2f pos) {
    shape->setPosition(pos.x +BATTLESHIP_PADDING,pos.y+BATTLESHIP_PADDING);
    return *this;
};
BattleShip& BattleShip::setCoords(sf::Vector2i _coords) {
    coords = _coords;
    return *this;
};
bool BattleShip::canDrop(std::array<BattleShip*, 7> ships) {
    if(!((direction == "horizontal" && coords.x + length - 1 < TABLE_ROWS) || (direction == "vertical" && coords.y + length - 1 < TABLE_COLUMNS))) 
        return false;

    for(auto ship : ships) {
        if(ship != this && ship->shape->getGlobalBounds().intersects(shape->getGlobalBounds())) return false;
    }

    return true;
}