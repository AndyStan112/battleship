#include <SFML/Graphics.hpp>
#include <Array>
#include <iostream>
#include <string>
#include <algorithm>

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

class BattleShip {
    public:
    sf::Color color=sf::Color::Red;
    int length;
    int width;
    int height=32;
    sf::RectangleShape* shape ;
    int offset;
    std::string direction= "vertical";
    BattleShip(int _length){
        length= _length;
        width=40*length-8;
        shape = new sf::RectangleShape(sf::Vector2f(width, height));
        // offset=user=="enemy"?640:0;
        shape->setFillColor(color);
        shape->setOutlineThickness(1);
        shape->setPosition(13, 13);
    }
    BattleShip& rotate(){
        if(direction=="vertical"){
            direction="horizontal";
            std::swap(width,height);
            shape->setSize(sf::Vector2f(width,height));
        }
        else{
            direction="vertical";
            std::swap(width,height);
            shape->setSize(sf::Vector2f(width,height));
        }
          return *this;
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
    BattleShip* userShips[7] = {new BattleShip(5),new BattleShip(4),new BattleShip(3),new BattleShip(2),new BattleShip(2),new BattleShip(1),new BattleShip(1)};

    BattleShip selectedShip = BattleShip(2);
    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    selectedShip.rotate();
                }
             }
        }

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
       window.draw(*selectedShip.shape);
        window.display();
    }

    return 0;
}