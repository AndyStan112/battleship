#include <SFML/Graphics.hpp>
#include <Array>
#include <iostream>
#include <string>
#include <algorithm>
#include "BattleShip.cpp"
const int SNAP = 40; 

class GameTile {
    public:
    std::string user;
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(40, 40));
     int offset;
    GameTile(std::string _user,int i,int j){
        user=_user;
        sf::Color color= user =="user"? sf::Color::Cyan: sf::Color::Black;
        offset=user=="enemy"?640:0;
        shape->setFillColor(color);
        shape->setOutlineThickness(2);
        shape->setPosition(10 + 40 * i + offset, 10+ 40*j);
    }
};


class GameGrid {
    public:
    std::array<std::array<GameTile*,10>,10> grid;
    std::string user;
   
    GameGrid( std::string _user){
        user=_user;
        
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                grid[i][j] = new GameTile(user,i,j);
            }
        }
        std::cout<<"test";
    }
};

int main()
{  
   
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    GameGrid userGrid= GameGrid("user");
    GameGrid enemyGrid= GameGrid("enemy");
    BattleShip* userShips[7] = {new BattleShip(5,0),new BattleShip(4,1),new BattleShip(3,2),new BattleShip(2,3),new BattleShip(2,4),new BattleShip(1,5),new BattleShip(1,6)};

    BattleShip* selectedShip = NULL;
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        auto mouseCoords = window.mapPixelToCoords(mousePosition);
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   for(auto ship:userShips){
                    if(ship->shape->getGlobalBounds().contains(mouseCoords))
                        selectedShip=ship;
                   }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R && selectedShip) {
                    selectedShip->rotate();
                }
                if(event.key.code == sf::Keyboard::Q)window.close();
             }
        }
        if(selectedShip){if(true)selectedShip->shape->setPosition(mouseCoords);}
        window.clear();
        //draw
        for(auto row: userGrid.grid){
           for(auto tile: row){
            window.draw(*tile->shape);
           }
        }
        for(auto row: enemyGrid.grid){
           for(auto tile: row){
            window.draw(*tile->shape);
           }
        }
        for(auto ship: userShips){
            window.draw(*ship->shape);
           }
        window.display();
    }

    return 0;
}