#include "Road.h"

Road::Road(sf::Vector2f position, bool isVertical)
{   
    if (isVertical)
        roadSurface.setSize(sf::Vector2f(100.f, 800.f));
    else
        roadSurface.setSize(sf::Vector2f(800.f, 100.f));
    
    roadSurface.setPosition(position);
    roadSurface.setFillColor(sf::Color::White);

    sf::Vector2f roadPosition = roadSurface.getPosition();
    sf::Vector2f roadSize = roadSurface.getSize();
    float centerX = roadPosition.x + roadSize.x / 2;
    float centerY = roadPosition.y + roadSize.y / 2;

    if (isVertical) {
        roadLines.setSize(sf::Vector2f(2.f, roadSize.y));
        roadLines.setPosition(centerX - 1.f, roadPosition.y); 
    } else {
        roadLines.setSize(sf::Vector2f(roadSize.x, 2.f));
        roadLines.setPosition(roadPosition.x, centerY - 1.f); 
    }

    roadLines.setFillColor(sf::Color::Red);
}

const sf::RectangleShape &Road::getRoadSurface() const
{
    return roadSurface;
}

const sf::RectangleShape &Road::getRoadLines() const
{
    return roadLines;
}