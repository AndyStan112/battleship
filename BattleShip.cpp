    #include "BattleShip.h"

    BattleShip::BattleShip(int _length, int index){
        color=sf::Color::Green;
        coords=sf::Vector2i(0,0);
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
    BattleShip  &BattleShip::setColor(sf::Color _color){
        color = _color;
        shape->setFillColor(color);
    };
    BattleShip  &BattleShip::setPos(sf::Vector2f pos){
       shape->setPosition(3+pos.x,3+pos.y);
    };
    BattleShip  &BattleShip::setCoords(sf::Vector2i _coords){
       coords= _coords;
    };
    bool BattleShip::fits(){
       return  direction=="horizontal" &&  coords.x+length-1<10||direction=="vertical" &&  coords.y+length-1<10;
    }