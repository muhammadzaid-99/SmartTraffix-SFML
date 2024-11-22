#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "TrafficLight.h"
#include "ProbabilityGenerator.h"
#include "Road.h"
#include "CommonEnums.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <unordered_map>

struct VehicleSpawnTimer
{
    float interval;    // The spawn interval for the timer
    float elapsed;     // The elapsed time for this timer
    float probability; // The probability of spawning a vehicle
    RoadEdge roadEdge;
    VehicleType vehicleType;
};

class Simulation
{
private:
    sf::Font font;
    sf::Text timeText;
    sf::Text roadLengthText;
    sf::RenderWindow window;
    std::vector<Vehicle *> vehicles;
    std::vector<TrafficLight> trafficLights;
    std::unordered_map<RoadEdge, Road *> roads;
    unsigned int screenWidth;
    float simulationElapsedTime;
    std::vector<VehicleSpawnTimer> vehicleSpawnTimers;
    ProbabilityGenerator pg;

public:
    // Constructor
    Simulation(unsigned int screenWidth);

    // Destructor
    ~Simulation();

    // Runs the simulation
    void run();
    void addVehicle(RoadEdge roadEdge, VehicleType vehicleType, std::string numberPlate);

private:
    // Handles events such as window closure
    void handleEvents();

    void spawnVehicles(float deltaTime);

    // Updates the simulation state
    void update(float deltaTime);

    // Renders the simulation
    void render();

    void initTexts();
};

#endif // SIMULATION_H
