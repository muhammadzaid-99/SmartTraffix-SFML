#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "TrafficLight.h"
#include "Road.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct VehicleSpawnTimer {
    float interval;   // The spawn interval for the timer
    float elapsed;    // The elapsed time for this timer
    Vehicle vehicle;
};

class Simulation {
private:
    sf::RenderWindow window;
    std::vector<Vehicle*> vehicles;
    std::vector<TrafficLight> trafficLights;
    std::vector<Road> roads;
    unsigned int screenWidth;
    float elapsedTime;
    std::vector<VehicleSpawnTimer> vehicleSpawnTimers;

public:
    // Constructor
    Simulation(unsigned int screenWidth);

    // Destructor
    ~Simulation();

    // Runs the simulation
    void run();
    void addVehicle(const Vehicle& vehicle);

private:
    // Handles events such as window closure
    void handleEvents();

    void spawnVehicles(float deltaTime);

    // Updates the simulation state
    void update(float deltaTime);

    // Renders the simulation
    void render();
};

#endif // SIMULATION_H
