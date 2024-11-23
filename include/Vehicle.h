#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "ProbabilityGenerator.h"

class Vehicle {
   protected:
    sf::Text numberPlate;
    sf::RectangleShape shape;
    float speed;
    float maxSpeed;
    bool challanActive;
    float elapsedTime;
    sf::Vector2i direction;
    bool isStopped;
    bool isOutOfOrder;

   public:
    // Constructor
    Vehicle(sf::Text plate, sf::Vector2f position, sf::Color color, float initialSpeed, float maxSpeed, sf::Vector2i direction);

    // Updates the position of the vehicle
    void updatePosition(float deltaTime);

    // Increases the speed of the vehicle
    void increaseSpeed(float increment);

    void decreaseSpeed(float decrement);

    // Returns the shape of the vehicle
    const sf::RectangleShape& getShape() const;

    // Activates a challan for the vehicle
    void activateChallan();

    // Checks if a challan is active for the vehicle
    bool isChallanActive() const;

    void setDirection(sf::Vector2i);

    static bool areVehiclesAtSafeDistance(const Vehicle& v1, const Vehicle& v2);

    const float& getElapsedTime() const;
    void setElapsedTime(float elapsed);
    const sf::Vector2f getPosition() const;
    const sf::Vector2i getDirection() const;
    const float& getSpeed() const;
    void setSpeed(float speed);
    void setIsStopped(bool);
    const bool& getIsStopped() const;

    const bool& getIsOutOfOrder() const;
    void setOutOfOrder(bool);

    const float& getMaxSpeed() const;
    const sf::Text& getNumberPlate() const;
};

// Derived class for Light Vehicle
class LightVehicle : public Vehicle {
   public:
    LightVehicle(sf::Text plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color);
};

// Derived class for Heavy Vehicle
class HeavyVehicle : public Vehicle {
   public:
    HeavyVehicle(sf::Text plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color);
};

// Derived class for Emergency Vehicle
class EmergencyVehicle : public Vehicle {
   public:
    EmergencyVehicle(sf::Text plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color);
};

#endif  // VEHICLE_H
