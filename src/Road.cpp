#include "Road.h"

Road::Road(sf::Vector2f position, bool isVertical, sf::Vector2i direction) : direction(direction)
{   
    if (isVertical)
        roadSurface.setSize(sf::Vector2f(100.f, 800.f));
    else
        roadSurface.setSize(sf::Vector2f(800.f, 100.f));

    roadSurface.setPosition(position);
    roadSurface.setFillColor(sf::Color::White);

    sf::Vector2f roadPosition = roadSurface.getPosition();
    sf::Vector2f roadSize = roadSurface.getSize();
    float centerX = roadPosition.x + roadSize.x / 2;
    float centerY = roadPosition.y + roadSize.y / 2;

    // vehicle width is 20.f, length is 40.f
    // lane width if 50.f, 15.f is the margin in lane from car to road

    if (isVertical) {
        roadLines.setSize(sf::Vector2f(2.f, roadSize.y));
        roadLines.setPosition(centerX - 1.f, roadPosition.y); 
        if (direction.y == 1) { // down
            fastLaneVehiclesInitPos.y = slowLaneVehiclesInitPos.y = 0.f;
            fastLaneVehiclesInitPos.x = roadPosition.x + 15.f;
            slowLaneVehiclesInitPos.x = centerX + 15.f;
        } else { // up
            fastLaneVehiclesInitPos.y = slowLaneVehiclesInitPos.y = 760.f;
            fastLaneVehiclesInitPos.x = centerX + 15.f;
            slowLaneVehiclesInitPos.x = roadPosition.x + 15.f;
        }
    } else {
        roadLines.setSize(sf::Vector2f(roadSize.x, 2.f));
        roadLines.setPosition(roadPosition.x, centerY - 1.f); 
        if (direction.x == 1) {  // right
            fastLaneVehiclesInitPos.x = slowLaneVehiclesInitPos.x = 0.f;
            fastLaneVehiclesInitPos.y = centerY + 15.f;
            slowLaneVehiclesInitPos.y = roadPosition.y + 15.f;
        } else {  // left
            fastLaneVehiclesInitPos.x = slowLaneVehiclesInitPos.x = 760.f;
            fastLaneVehiclesInitPos.y = roadPosition.y + 15.f;
            slowLaneVehiclesInitPos.y = centerY + 15.f;
        }
    }

    roadLines.setFillColor(sf::Color::Red);
}

void Road::addVehicle(std::string numberPlate, VehicleType vt)
{
    Vehicle* vehicle;

    if (vt == VehicleType::HTV) {
        vehicle = new HeavyVehicle(numberPlate, slowLaneVehiclesInitPos, direction);
        slowLaneVehicles.push_back(vehicle);
        return;
    }

    if (vt == VehicleType::LTV)
        vehicle = new LightVehicle(numberPlate, fastLaneVehiclesInitPos, direction);
    else if (vt == VehicleType::EV)
        vehicle = new EmergencyVehicle(numberPlate, fastLaneVehiclesInitPos, direction);

    fastLaneVehicles.push_back(vehicle);
}

const sf::RectangleShape &Road::getRoadSurface() const
{
    return roadSurface;
}

const sf::RectangleShape &Road::getRoadLines() const
{
    return roadLines;
}

const std::vector<Vehicle*>& Road::getFastLaneVehicles() const {
    return fastLaneVehicles;
}
const std::vector<Vehicle*>& Road::getSlowLaneVehicles() const {
    return slowLaneVehicles;
}