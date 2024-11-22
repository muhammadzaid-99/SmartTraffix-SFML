#include "Vehicle.h"

Vehicle::Vehicle(std::string plate, sf::Vector2f position, sf::Color color, float initialSpeed, float maxSpeed, sf::Vector2i direction)
    : numberPlate(plate), speed(initialSpeed), maxSpeed(maxSpeed), challanActive(false), direction(direction)
{
    if (direction.x == 0)
        shape.setSize(sf::Vector2f(20.f, 40.f));
    else
        shape.setSize(sf::Vector2f(40.f, 20.f));
    shape.setPosition(position);
    shape.setFillColor(color);

    elapsedTime = 0.f;
}

void Vehicle::updatePosition(float deltaTime)
{
    shape.move(speed * deltaTime * direction.x, speed * deltaTime * direction.y);
    elapsedTime += deltaTime;
}

const sf::Vector2f Vehicle::getPosition() const {
    return shape.getPosition();
}

const sf::Vector2i Vehicle::getDirection() const {
    return direction;
}

void Vehicle::increaseSpeed(float increment)
{
    speed = std::min(increment + speed, maxSpeed);
}

void Vehicle::decreaseSpeed(float decrement) {
    speed = std::max(0.f, speed - decrement);
}

const sf::RectangleShape &Vehicle::getShape() const
{
    return shape;
}

const float& Vehicle::getSpeed() const
{
    return speed;
}

void Vehicle::setSpeed(float speed) {
    this->speed = speed;
}

const float& Vehicle::getElapsedTime() const {
    return elapsedTime;
}

void Vehicle::setElapsedTime(float elapsed) {
    elapsedTime = elapsed;
}

const float& Vehicle::getMaxSpeed() const {
    return maxSpeed;
}

void Vehicle::activateChallan()
{
    challanActive = true;
}

bool Vehicle::isChallanActive() const
{
    return challanActive;
}

bool Vehicle::areVehiclesAtSafeDistance(const Vehicle &v1, const Vehicle &v2) // static
{
    sf::Vector2f v1Pos = v1.getPosition();
    sf::Vector2f v2Pos = v2.getPosition();
    sf::Vector2f v1Size = v1.getShape().getSize();
    sf::Vector2f v2Size = v2.getShape().getSize();
    const float v1Speed = v1.getSpeed();
    const float v2Speed = v2.getSpeed();
    sf::Vector2i direction = v1.getDirection(); // Assuming the same for both vehicles

    // Calculate next positions based on direction and speed
    sf::Vector2f v1NextPos = v1Pos + sf::Vector2f(v1Speed * direction.x, v1Speed * direction.y);
    sf::Vector2f v2NextPos = v2Pos + sf::Vector2f(v2Speed * direction.x, v2Speed * direction.y);

    // Calculate safety margin in each direction
    float safetyMarginX = v1Size.x;
    float safetyMarginY = v1Size.y;

    // Check if vehicles overlap in the next positions
    bool isSafeX = std::abs(v1NextPos.x - v2NextPos.x) > safetyMarginX;
    bool isSafeY = std::abs(v1NextPos.y - v2NextPos.y) > safetyMarginY;

    // Vehicles are at a safe distance if they don't overlap in either direction
    return isSafeX || isSafeY;
}
 
// suppose road is SCREEN_WIDTH / 8 metres long (100m)
LightVehicle::LightVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color color)
    : Vehicle(plate, position, color, initialSpeed, maxSpeed, direction) {
    // maxSpeed = 16.6667f * 8; // 60km/h = 16.667m/s
    // speed = pg.getRandomProb(1.f, maxSpeed);
    }

HeavyVehicle::HeavyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color color)
    : Vehicle(plate, position, color, initialSpeed, maxSpeed, direction) {
    // maxSpeed = 11.1111f * 8; // 40km/h = 11.11m/s
    // speed = pg.getRandomProb(1.f, maxSpeed);
    }

EmergencyVehicle::EmergencyVehicle(std::string plate, sf::Vector2f position, sf::Vector2i direction, float initialSpeed, float maxSpeed, sf::Color color)
    : Vehicle(plate, position, color, initialSpeed, maxSpeed, direction) {
    // maxSpeed = 22.2222f * 8; // 80km/h = 22.22m/s
    // speed = pg.getRandomProb(1.f, maxSpeed);
    }
