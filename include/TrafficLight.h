#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <SFML/Graphics.hpp>

class TrafficLight {
private:
    sf::CircleShape shape;
    sf::Color currentColor; // Red, Yellow, Green
    float timer;
    float duration[3]; // {Red, Yellow, Green} durations in seconds

public:
    // Constructor
    TrafficLight(sf::Vector2f position);

    // Update method to handle the traffic light logic
    void update(float deltaTime);

    // Getter for the shape
    const sf::CircleShape& getShape() const;

    void move(float x, float y);


    // Getter for the current color
    sf::Color getColor() const;

    // Setter for the position of the traffic light
    void setPosition(sf::Vector2f position);

    void setColor(sf::Color color);

    // Setter for the duration of the traffic light colors
    void setDuration(float redDuration, float yellowDuration, float greenDuration);
};

#endif // TRAFFIC_LIGHT_H
