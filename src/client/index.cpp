#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <string>
#include <algorithm>
#include "constants/constants.h"
#include "layout/utils/node.h"
#include "display/display.cpp"
#include "layout/engine.cpp"
#include "shapes/RoundedRectangle.cpp"

int main()
{
    // sf::Font font;
    // if (!font.loadFromFile("./assets/fonts/FuturaBold.ttf"))
    //     throw "Font missing! Please download Futura Bold Font!";

    Display *display = new Display(DEFAULT_DISPLAY_WIDTH, DEFAULT_DISPLAY_HEIGHT);

    sf::RenderWindow window(sf::VideoMode(display->width, display->height), "BATTLESHIP 🛡️🚢");

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        Node* E1 = new Node(), *E2 = new Node(), *E3 = new Node(), *E4 = new Node(), *E8 = new Node(), *E9 = new Node();
        E1->shape = new sf::RectangleShape(sf::Vector2f(150, 150));
        E1->margin.right = 10;
        E1->margin.left = 10;
        E1->margin.top = 10;
        E1->name = "E1";
        E1->shape->setFillColor(sf::Color::Blue);
        
        E2->shape = new sf::RectangleShape(sf::Vector2f(200, 150));
        E2->margin.right = 10;
        E2->margin.top = 10;
        E2->shape->setFillColor(sf::Color::Green);
        E2->name = "E2";
        
        E3->shape = new sf::RoundedRectangleShape(sf::Vector2f(150, 150), 15);
        E3->margin.right = 10;
        E3->margin.top = 10;
        E3->shape->setFillColor(sf::Color::Magenta);
        E3->name = "E3";

        E4->shape = new sf::RoundedRectangleShape(sf::Vector2f(150, 150), 15);
        E4->margin.right = 10;
        E4->margin.top = 10;
        E4->shape->setFillColor(sf::Color::Red);
        E4->name = "E4";

        E8->shape = new sf::RoundedRectangleShape(sf::Vector2f(150, 150), 15);
        E8->margin.right = 10;
        E8->margin.top = 10;
        E8->shape->setFillColor(sf::Color::Green);
        E8->name = "E8";

        E9->shape = new sf::RoundedRectangleShape(sf::Vector2f(150, 150), 15);
        E9->margin.right = 10;
        E9->margin.top = 10;
        E9->shape->setFillColor(sf::Color::Magenta);
        E9->name = "E9";

        Node *E5 = new Node(), *E6 = new Node(), *E7 = new Node();
        E5->children = {E1, E2};
        E5->margin.top = 20;
        E5->margin.left = 50;
        E5->padding.right = 50;
        E5->padding.left = 50;
        E5->shape->setFillColor(sf::Color::Yellow);
        E5->name = "E5";
        
        E6->children = {E3, E4};
        E6->shape->setFillColor(sf::Color::Cyan);
        E6->name = "E6";
        E6->margin.top = 20;

        E7->children = {E8, E9};
        E7->shape->setFillColor(sf::Color::Yellow);
        E7->name = "E7";
        E7->margin.top = 20;

        Node *root = new Node();
        root->children = {E5, E6, E7};
        root->name = "root";

        ComputeLayout(root, DEFAULT_DISPLAY_WIDTH, window);

        window.display();
    }

    return 0;
}