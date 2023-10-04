#pragma once

#include <SFML/Graphics.hpp>
#include "../constants/constants.h"
#include "../shapes/RoundedRectangle.h"
#include "../layout/utils/node.h"

class Pip : public Node {
    public: 
    sf::Shape *shape = new sf::CircleShape(GRID_CELL_SIZE / 4);
    
    bool showPip = false;
};

class GameTile : public Node {
    public:
    std::vector<Pip*> children;
    sf::Shape *shape = new sf::RoundedRectangleShape(sf::Vector2f(GRID_CELL_SIZE, GRID_CELL_SIZE), 4, 10);

    GameTile(int i, int j, sf::Color color);
};

