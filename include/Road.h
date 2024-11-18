#ifndef ROAD_H
#define ROAD_H

#include <SFML/Graphics.hpp>

class Road {
    private:
    sf::RectangleShape shape;
    sf::Color currentColor;
public:
    Road(sf::Vector2f position, bool isVertical);

    const sf::RectangleShape& getShape() const;
};

#endif