#include "TrafficLight.h"
TrafficLight::TrafficLight(sf::Vector2f position)
    : currentColor(sf::Color::Red), timer(0.f), duration{10.f, 2.f, 8.f}
{
    shape.setSize(sf::Vector2f(20.f, 60.f));
    shape.setPosition(position);
    shape.setFillColor(currentColor);
}

void TrafficLight::update(float deltaTime)
{
    timer += deltaTime;

    // Switch traffic light color based on timer
    if (currentColor == sf::Color::Red && timer >= duration[0])
    {
        currentColor = sf::Color::Green;
        timer = 0.f;
    }
    else if (currentColor == sf::Color::Green && timer >= duration[2])
    {
        currentColor = sf::Color::Yellow;
        timer = 0.f;
    }
    else if (currentColor == sf::Color::Yellow && timer >= duration[1])
    {
        currentColor = sf::Color::Red;
        timer = 0.f;
    }

    shape.setFillColor(currentColor);
}

const sf::RectangleShape &TrafficLight::getShape() const
{
    return shape;
}

sf::Color TrafficLight::getColor() const
{
    return currentColor;
}
