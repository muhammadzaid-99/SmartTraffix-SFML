#ifndef ROAD_H
#define ROAD_H

#include <SFML/Graphics.hpp>
#include "Vehicle.h"
#include "CommonEnums.h"
#include "ProbabilityGenerator.h"
#include "TrafficLight.h"

class Road {
private:
    sf::RectangleShape roadSurface;
    sf::Color currentColor;
    sf::RectangleShape roadLines;
    sf::Vector2i direction;
    sf::Vector2f fastLaneVehiclesInitPos;
    sf::Vector2f slowLaneVehiclesInitPos;
    sf::Vector2f fastLaneVehiclesFinalPos;
    sf::Vector2f slowLaneVehiclesFinalPos;
    std::vector<Vehicle*> fastLaneVehicles;
    std::vector<Vehicle*> slowLaneVehicles;
    TrafficLight trafficLight;
    sf::RectangleShape trafficLightIntersector;
    ProbabilityGenerator pg;

public:
    Road(sf::Vector2f position, bool isVertical, sf::Vector2i direction);
    ~Road();

    void addVehicle(sf::Text numberPlate, VehicleType vt);

    const sf::RectangleShape& getRoadSurface() const;
    const sf::RectangleShape& getRoadLines() const;
    const sf::RectangleShape& getIntersectorLine() const;
    const sf::CircleShape& getTrafficLight() const;
    const std::vector<Vehicle*>& getFastLaneVehicles() const;
    const std::vector<Vehicle*>& getSlowLaneVehicles() const;
    void updateTrafficLight(float deltaTime);

    void removeLeftVehicles();
    void setTrafficLightColor(sf::Color color);
};

#endif