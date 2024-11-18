#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <string>

class Vehicle {
protected:
    std::string numberPlate;
    sf::RectangleShape shape;
    float speed;
    bool challanActive;
    sf::Vector2i direction;

public:
    // Constructor
    Vehicle(std::string plate, sf::Vector2f position, sf::Color color, float initialSpeed, sf::Vector2i direction);

    // Updates the position of the vehicle
    void updatePosition(float deltaTime);

    // Increases the speed of the vehicle
    void increaseSpeed(float increment);

    // Returns the shape of the vehicle
    const sf::RectangleShape& getShape() const;

    // Activates a challan for the vehicle
    void activateChallan();

    // Checks if a challan is active for the vehicle
    bool isChallanActive() const;
};

// Derived class for Light Vehicle
class LightVehicle : public Vehicle {
public:
    LightVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction);
};

// Derived class for Heavy Vehicle
class HeavyVehicle : public Vehicle {
public:
    HeavyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction);
};

// Derived class for Emergency Vehicle
class EmergencyVehicle : public Vehicle {
public:
    EmergencyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction);
};

#endif // VEHICLE_H
