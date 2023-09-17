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
     sf::Vector2f pos;
    GameTile(std::string _user,int i,int j){
        user=_user;
        sf::Color color= user =="user"? sf::Color::Cyan: sf::Color::Black;
        offset=user=="enemy"?640:0;
        pos.x=10 + 40 * i + offset;
        pos.y= 10+ 40*j;
        shape->setFillColor(color);
        shape->setOutlineThickness(2);
        shape->setPosition(pos.x,pos.y );
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
    sf::Vector2f getClosestPos(sf::Vector2f coords,BattleShip* ship ){
        sf::Vector2i closestCoords= getClosestCoords(coords,ship);
        return grid[closestCoords.x][closestCoords.y]->pos;
    }
    sf::Vector2i getClosestCoords(sf::Vector2f coords,BattleShip* ship ){
        coords.x -=10;
        coords.y -=10;
        int i =int(coords.x)/40;
        int j =int(coords.y)/40;
         i = std::max(0, std::min(9, i));
         j = std::max(0, std::min(9, j));
        
        return sf::Vector2i(i,j);
    }
    bool isOutside(sf::Vector2f pos){
        return pos.x>=10+400||pos.y>=10+400;
    }
};

int main()
{  
   
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");
    GameGrid userGrid= GameGrid("user");
    GameGrid enemyGrid= GameGrid("enemy");
    std::array<BattleShip*, 7> userShips = {new BattleShip(5,0),new BattleShip(4,1),new BattleShip(3,2),new BattleShip(2,3),new BattleShip(2,4),new BattleShip(1,5),new BattleShip(1,6)};

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
                    if(selectedShip && selectedShip->canDrop()) {
                        // make the cursor visible (exit "drag&drop" feel)
                        window.setMouseCursorVisible(true);
                                            
                        // if the ship is outside the board
                        if(userGrid.isOutside(mouseCoords))
                            // place the ship back in the "selection list"
                            selectedShip->reset();
                        else 
                            // otherwise place the ship on the board
                            selectedShip->fixed=true;
                        
                        selectedShip=NULL;
                    }
                    
                    // if the user clicked inside the window and doesn't hold a ship
                    else 
                        for(auto ship : userShips)
                            // check if he is trying to grab a ship from the "selection list"
                            if(ship->shape->getGlobalBounds().contains(mouseCoords))
                            {
                                // make the cursor invisible (create a "drag&drop" feel)
                                window.setMouseCursorVisible(false);
                                
                                selectedShip=ship;
                                break;
                            }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R && selectedShip)
                    selectedShip->rotate();
                if(event.key.code == sf::Keyboard::Q) 
                    window.close();
            }
        }


        if(selectedShip){
           
            // if the user holds a ship, but is outside the board
            if(userGrid.isOutside(mouseCoords)) {
                // make the ship follow the cursor (disable the snapping feel) and change the color to red 
                 selectedShip->setPos(mouseCoords).setCoords(sf::Vector2i(0, 0)).setColor(sf::Color::Red);
            }

            // if the user holds a ship and is inside the board
            else {

                // the position of the closest grid cell (e.g: {x: 50px y: 90px})
                auto shipPos = userGrid.getClosestPos(mouseCoords,selectedShip);
                 
                // the index of the closest grid cell (e.g. {i: 1, j: 2});
                auto shipCoords = userGrid.getClosestCoords(mouseCoords,selectedShip);
                
                // snap the ship to the closest grid cell 
                selectedShip->setPos(shipPos).setCoords(shipCoords);

                if(selectedShip->canDrop())
                    selectedShip->setColor(sf::Color::Green);
                else 
                    selectedShip->setColor(sf::Color::Red);
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
        for(auto ship: userShips){
            window.draw(*ship->shape);
           }
        window.display();
    }

    return 0;
}