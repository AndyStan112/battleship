#include <SFML/Graphics.hpp>
#include <Array>
#include <iostream>
#include <string>

class GameTile {
    public:
    std::string user;
    sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(40, 40));
     int offset;
    GameTile(std::string _user,int i,int j){
        user=_user;
        offset=user=="enemy"?640:0;
        shape->setFillColor(sf::Color::Cyan);
        shape->setOutlineThickness(2);
        shape->setPosition(10 + 41 * i + offset, 10+ 41*j);
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
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
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
       
        window.display();
    }

    return 0;
}