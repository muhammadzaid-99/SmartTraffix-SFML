#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, sf::Vector2f position, sf::Color color, float initialSpeed, sf::Vector2i direction)
    : numberPlate(plate), speed(initialSpeed), challanActive(false), direction(direction)
{
    if (direction.x == 0)
        shape.setSize(sf::Vector2f(20.f, 40.f));
    else
        shape.setSize(sf::Vector2f(40.f, 20.f));
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Vehicle::updatePosition(float deltaTime)
{
    shape.move(speed * deltaTime * direction.x, speed * deltaTime * direction.y);
}

const sf::Vector2f Vehicle::getPosition() const {
    return shape.getPosition();
}

const sf::Vector2i Vehicle::getDirection() const {
    return direction;
}

void Vehicle::increaseSpeed(float increment)
{
    speed += increment;
}

const sf::RectangleShape &Vehicle::getShape() const
{
    return shape;
}

void Vehicle::activateChallan()
{
    challanActive = true;
}

bool Vehicle::isChallanActive() const
{
    return challanActive;
}

LightVehicle::LightVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction)
    : Vehicle(plate, position, sf::Color::Cyan, 40.f, direction) {}

HeavyVehicle::HeavyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction)
    : Vehicle(plate, position, sf::Color::Blue, 5.f, direction) {}

EmergencyVehicle::EmergencyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction)
    : Vehicle(plate, position, sf::Color::Red, 50.f, direction) {}
