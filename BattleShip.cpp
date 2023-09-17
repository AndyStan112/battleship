    #include "BattleShip.h"

    BattleShip::BattleShip(int _length, int index){
        color=sf::Color::Green;
        length= _length;
        height=40*length-8;
        width=32;
        offset = 40*index ;
        shape = new sf::RectangleShape(sf::Vector2f(width, height));
        // offset=user=="enemy"?640:0;
        shape->setFillColor(color);
        shape->setOutlineThickness(1);
        shape->setPosition(13+offset,720- 53-height);
    };

    BattleShip &BattleShip::rotate(){
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
    };