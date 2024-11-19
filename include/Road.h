#ifndef ROAD_H
#define ROAD_H

#include <SFML/Graphics.hpp>

class Road {
    private:
    sf::RectangleShape roadSurface;
    sf::Color currentColor;
    sf::RectangleShape roadLines;
public:
    Road(sf::Vector2f position, bool isVertical);

    const sf::RectangleShape& getRoadSurface() const;
    const sf::RectangleShape& getRoadLines() const;
};

#endif