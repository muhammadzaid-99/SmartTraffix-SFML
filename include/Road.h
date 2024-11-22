#ifndef ROAD_H
#define ROAD_H

#include <SFML/Graphics.hpp>
#include "Vehicle.h"
#include "CommonEnums.h"
#include "ProbabilityGenerator.h"

class Road {
private:
    sf::RectangleShape roadSurface;
    sf::Color currentColor;
    sf::RectangleShape roadLines;
    sf::Vector2i direction;
    sf::Vector2f fastLaneVehiclesInitPos;
    sf::Vector2f slowLaneVehiclesInitPos;
    std::vector<Vehicle*> fastLaneVehicles;
    std::vector<Vehicle*> slowLaneVehicles;
    ProbabilityGenerator pg;

public:
    Road(sf::Vector2f position, bool isVertical, sf::Vector2i direction);
    void addVehicle(std::string numberPlate, VehicleType vt);

    const sf::RectangleShape& getRoadSurface() const;
    const sf::RectangleShape& getRoadLines() const;
    const std::vector<Vehicle*>& getFastLaneVehicles() const;
    const std::vector<Vehicle*>& getSlowLaneVehicles() const;
};

#endif