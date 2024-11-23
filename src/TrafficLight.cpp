#include "TrafficLight.h"
TrafficLight::TrafficLight(sf::Vector2f position)
    : currentColor(sf::Color::Green), timer(0.f), duration{8.f, 3.f, 10.f} {
    shape.setRadius(10.f);
    shape.setFillColor(currentColor);
    shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
    shape.setPosition(position);
}

void TrafficLight::update(float deltaTime) {
    timer += deltaTime;

    // Switch traffic light color based on timer
    if (currentColor == sf::Color::Red && timer >= duration[0]) {
        currentColor = sf::Color::Green;
        timer = 0.f;
    } else if (currentColor == sf::Color::Green && timer >= duration[2]) {
        currentColor = sf::Color::Yellow;
        timer = 0.f;
    } else if (currentColor == sf::Color::Yellow && timer >= duration[1]) {
        currentColor = sf::Color::Red;
        timer = 0.f;
    }

    shape.setFillColor(currentColor);
}

const sf::CircleShape &TrafficLight::getShape() const {
    return shape;
}

const sf::Vector2f &TrafficLight::getPosition() const {
    return shape.getPosition();
}

sf::Color TrafficLight::getColor() const {
    return currentColor;
}

void TrafficLight::move(float x, float y) {
    shape.move(x, y);
}

void TrafficLight::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
}

void TrafficLight::setColor(sf::Color color) {
    currentColor = color;
    shape.setFillColor(currentColor);
}

void TrafficLight::setDuration(float redDuration, float yellowDuration, float greenDuration) {
    duration[0] = redDuration;
    duration[1] = yellowDuration;
    duration[2] = greenDuration;
}