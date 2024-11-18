#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <SFML/Graphics.hpp>

class TrafficLight {
private:
    sf::RectangleShape shape;
    sf::Color currentColor; // Red, Yellow, Green
    float timer;
    float duration[3]; // {Red, Yellow, Green} durations in seconds

public:
    // Constructor
    TrafficLight(sf::Vector2f position);

    // Update method to handle the traffic light logic
    void update(float deltaTime);

    // Getter for the shape
    const sf::RectangleShape& getShape() const;

    // Getter for the current color
    sf::Color getColor() const;
};

#endif // TRAFFIC_LIGHT_H
