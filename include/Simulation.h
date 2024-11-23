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
    sf::Text elapsedTimeText;
    sf::Text currentTimeText;
    sf::Text roadLengthText;
    sf::RenderWindow window;
    float currentTimeOffset;
    std::unordered_map<RoadEdge, Road *> roads;
    unsigned int screenWidth;
    float simulationElapsedTime;
    std::vector<VehicleSpawnTimer> vehicleSpawnTimers;
    ProbabilityGenerator pg;
    unsigned lastVehicleId;
    bool isPeakTime;

public:
    // Constructor
    Simulation(unsigned int screenWidth);

    // Destructor
    ~Simulation();

    // Runs the simulation
    void run();
    void addVehicle(RoadEdge roadEdge, VehicleType vehicleType, sf::Text numberPlate);

private:
    // Handles events such as window closure
    void handleEvents();

    void spawnVehicles(float deltaTime);

    // Updates the simulation state
    void update(float deltaTime);

    // Renders the simulation
    void render();


    std::string updatedAndGetFormattedTime(int hour, int minute, int second);

    const sf::Text& getCurrentTimeText();

    void initTexts();
};

#endif // SIMULATION_H
