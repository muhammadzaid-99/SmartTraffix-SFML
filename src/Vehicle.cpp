#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, sf::Vector2f position, sf::Color color, float initialSpeed)
    : numberPlate(plate), speed(initialSpeed), challanActive(false)
{
    shape.setSize(sf::Vector2f(40.f, 20.f));
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Vehicle::updatePosition(float deltaTime)
{
    shape.move(speed * deltaTime, 0);
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

LightVehicle::LightVehicle(std::string plate, sf::Vector2f position)
    : Vehicle(plate, position, sf::Color::Cyan, 30.f) {}

HeavyVehicle::HeavyVehicle(std::string plate, sf::Vector2f position)
    : Vehicle(plate, position, sf::Color::Blue, 20.f) {}

EmergencyVehicle::EmergencyVehicle(std::string plate, sf::Vector2f position)
    : Vehicle(plate, position, sf::Color::Red, 50.f) {}
