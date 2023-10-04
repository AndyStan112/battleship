#pragma once
#include <SFML/Graphics/Shape.hpp>

namespace sf
{
    class RoundedRectangleShape : public sf::Shape
    {
        public:
            explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 5);
            
            void setSize(const Vector2f& size);
            
            const Vector2f& getSize() const;
            
            void setCornersRadius(float radius);
            
            float getCornersRadius() const;
            
            void setCornerPointCount(unsigned int count);
            
            virtual std::size_t getPointCount() const;
            
            virtual sf::Vector2f getPoint(std::size_t index) const;

        private:
            Vector2f mySize;
            float myRadius;
            unsigned int myCornerPointCount;
    };
}
