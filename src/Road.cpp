#include "Road.h"

Road::Road(sf::Vector2f position, bool isVertical)
{   
    if (isVertical)
        shape.setSize(sf::Vector2f(50.f, 800.f));
    else
        shape.setSize(sf::Vector2f(800.f, 50.f));
    
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

const sf::RectangleShape &Road::getShape() const
{
    return shape;
}