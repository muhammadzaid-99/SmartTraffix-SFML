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

    if (isVertical)
    {
        roadLines.setSize(sf::Vector2f(2.f, roadSize.y));
        roadLines.setPosition(centerX - 1.f, roadPosition.y);
        if (direction.y == 1)
        { // down
            fastLaneVehiclesInitPos.y = slowLaneVehiclesInitPos.y = 0.f;
            fastLaneVehiclesFinalPos.y = slowLaneVehiclesFinalPos.y = 800.f;
            fastLaneVehiclesInitPos.x = fastLaneVehiclesFinalPos.x = roadPosition.x + 15.f;
            slowLaneVehiclesInitPos.x = slowLaneVehiclesFinalPos.x = centerX + 15.f;
        }
        else
        { // up
            fastLaneVehiclesInitPos.y = slowLaneVehiclesInitPos.y = 760.f;
            fastLaneVehiclesFinalPos.y = slowLaneVehiclesFinalPos.y = -40.f;
            fastLaneVehiclesInitPos.x = fastLaneVehiclesFinalPos.x = centerX + 15.f;
            slowLaneVehiclesInitPos.x = slowLaneVehiclesFinalPos.x = roadPosition.x + 15.f;
        }
    }
    else
    {
        roadLines.setSize(sf::Vector2f(roadSize.x, 2.f));
        roadLines.setPosition(roadPosition.x, centerY - 1.f);
        if (direction.x == 1)
        { // right
            fastLaneVehiclesInitPos.x = slowLaneVehiclesInitPos.x = 0.f;
            fastLaneVehiclesFinalPos.x = slowLaneVehiclesFinalPos.x = 800.f;
            fastLaneVehiclesInitPos.y = fastLaneVehiclesFinalPos.y = centerY + 15.f;
            slowLaneVehiclesInitPos.y = slowLaneVehiclesFinalPos.y = roadPosition.y + 15.f;
        }
        else
        { // left
            fastLaneVehiclesInitPos.x = slowLaneVehiclesInitPos.x = 760.f;
            fastLaneVehiclesFinalPos.x = slowLaneVehiclesFinalPos.x = -40.f;
            fastLaneVehiclesInitPos.y = fastLaneVehiclesFinalPos.y = roadPosition.y + 15.f;
            slowLaneVehiclesInitPos.y = slowLaneVehiclesFinalPos.y = centerY + 15.f;
        }
    }

    roadLines.setFillColor(sf::Color(128, 128, 128)); // gray color
}

void Road::addVehicle(std::string numberPlate, VehicleType vt)
{
    Vehicle *vehicle;

    if (vt == VehicleType::HTV)
    {
        if (slowLaneVehicles.size() >= 10)
            return;

        // maxSpeed = 16.6667f * 8; // 60km/h = 16.667m/s
        vehicle = new HeavyVehicle(numberPlate, slowLaneVehiclesInitPos, direction, 40.f, 11.1111f * 8, sf::Color(0, 0, static_cast<sf::Uint8>(pg.getRandomProb(128, 255))));
        // if (slowLaneVehicles.size())
        //     vehicle->setSpeed(pg.getRandomProb(1.f, std::min(vehicle->getMaxSpeed(), slowLaneVehicles.front()->getSpeed())));
        // else
        vehicle->setSpeed(pg.getRandomProb(40.f, vehicle->getMaxSpeed()));
        slowLaneVehicles.push_back(vehicle);
        return;
    }

    if (fastLaneVehicles.size() >= 10)
        return;

    if (vt == VehicleType::LTV)
    {
        // maxSpeed = 11.1111f * 8; // 40km/h = 11.11m/s
        vehicle = new LightVehicle(numberPlate, fastLaneVehiclesInitPos, direction, 40.f, 16.6667f * 8, sf::Color(0, static_cast<sf::Uint8>(pg.getRandomProb(128, 255)), 0));
        // if (fastLaneVehicles.size())
        //     vehicle->setSpeed(pg.getRandomProb(40.f, std::min(vehicle->getMaxSpeed(), fastLaneVehicles.front()->getSpeed())));
        // else
            vehicle->setSpeed(pg.getRandomProb(40.f, vehicle->getMaxSpeed()));
    }
    else if (vt == VehicleType::EV)
    {
        // maxSpeed = 22.2222f * 8; // 80km/h = 22.22m/s
        vehicle = new EmergencyVehicle(numberPlate, fastLaneVehiclesInitPos, direction, 40.f, 22.2222f * 8, sf::Color(static_cast<sf::Uint8>(pg.getRandomProb(128, 255)), 0, 0));
        // if (fastLaneVehicles.size())
        //     vehicle->setSpeed(pg.getRandomProb(40.f, std::min(vehicle->getMaxSpeed(), fastLaneVehicles.front()->getSpeed())));
        // else
            vehicle->setSpeed(pg.getRandomProb(40.f, vehicle->getMaxSpeed()));
            std::cout << vehicle->getSpeed() << " & " << vehicle->getMaxSpeed() << std::endl;
    }

    fastLaneVehicles.push_back(vehicle);
}

void Road::removeLeftVehicles()
{
    for (auto it = fastLaneVehicles.begin(); it != fastLaneVehicles.end();)
    {
        if (direction.x == 1 && (*it)->getPosition().x > fastLaneVehiclesFinalPos.x)
        {
            delete *it; // unallocate memory for vehicle
            it = fastLaneVehicles.erase(it); // automatically does it++;
        }
        else if (direction.x == -1 && (*it)->getPosition().x < fastLaneVehiclesFinalPos.x)
        {
            delete *it; // unallocate memory for vehicle
            it = fastLaneVehicles.erase(it);
        }
        else if (direction.y == 1 && (*it)->getPosition().y > fastLaneVehiclesFinalPos.y)
        {
            delete *it; // unallocate memory for vehicle
            it = fastLaneVehicles.erase(it);
        }
        else if (direction.y == -1 && (*it)->getPosition().y < fastLaneVehiclesFinalPos.y)
        {
            delete *it; // unallocate memory for vehicle
            it = fastLaneVehicles.erase(it);
        }
        else
        {
            // ++it;
            break;
        }
    }

    for (auto it = slowLaneVehicles.begin(); it != slowLaneVehicles.end();)
    {
        if (direction.x == 1 && (*it)->getPosition().x > slowLaneVehiclesFinalPos.x)
        {
            delete *it;
            it = slowLaneVehicles.erase(it);
        }
        else if (direction.x == -1 && (*it)->getPosition().x < slowLaneVehiclesFinalPos.x)
        {
            delete *it;
            it = slowLaneVehicles.erase(it);
        }
        else if (direction.y == 1 && (*it)->getPosition().y > slowLaneVehiclesFinalPos.y)
        {
            delete *it;
            it = slowLaneVehicles.erase(it);
        }
        else if (direction.y == -1 && (*it)->getPosition().y < slowLaneVehiclesFinalPos.y)
        {
            delete *it;
            it = slowLaneVehicles.erase(it);
        }
        else
        {
            // ++it;
            break;
        }
    }
}
const sf::RectangleShape &Road::getRoadSurface() const
{
    return roadSurface;
}

const sf::RectangleShape &Road::getRoadLines() const
{
    return roadLines;
}

const std::vector<Vehicle *> &Road::getFastLaneVehicles() const
{
    return fastLaneVehicles;
}
const std::vector<Vehicle *> &Road::getSlowLaneVehicles() const
{
    return slowLaneVehicles;
}