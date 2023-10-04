#pragma once
#include <SFML/Graphics.hpp>

class Node {
    public: 
    std::vector<Node*> children;
    sf::RectangleShape* box = new sf::RectangleShape(sf::Vector2f(0, 0));
    sf::Shape* shape = new sf::RectangleShape(sf::Vector2f(0, 0));

    std::string name = "undefined";

    struct {
        int left = 0, right = 0, top = 0, bottom = 0;
    } padding;

    struct {
        int left = 0, right = 0, top = 0, bottom = 0;
    } margin;

    struct {
        int width = 0, height = 0;
    } dimensions;
    
};