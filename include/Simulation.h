#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "TrafficLight.h"
#include "Road.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Simulation {
private:
    sf::RenderWindow window;
    std::vector<Vehicle*> vehicles;
    std::vector<TrafficLight> trafficLights;
    std::vector<Road> roads;
    float elapsedTime;

public:
    // Constructor
    Simulation();

    // Destructor
    ~Simulation();

    // Runs the simulation
    void run();

private:
    // Handles events such as window closure
    void handleEvents();

    // Updates the simulation state
    void update(float deltaTime);

    // Renders the simulation
    void render();
};

#endif // SIMULATION_H
