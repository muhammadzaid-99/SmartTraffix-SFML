#include "Simulation.h"
Simulation::Simulation(unsigned int screenWidth) : window(sf::VideoMode(screenWidth, screenWidth), "SmartTraffix"), elapsedTime(0.f)
{
    unsigned sW = screenWidth;
    // Initialize roads cross-section
    roads.emplace_back(sf::Vector2f(0.f, sW / 2.f - 105), false);
    roads.emplace_back(sf::Vector2f(0.f, sW / 2.f + 5), false);
    roads.emplace_back(sf::Vector2f(sW / 2.f - 105, 0.f), true); 
    roads.emplace_back(sf::Vector2f(sW / 2.f + 5, 0.f), true); 

    // Initialize traffic lights
    // trafficLights.emplace_back(sf::Vector2f(370.f, 350.f)); // North
    // trafficLights.emplace_back(sf::Vector2f(370.f, 450.f)); // South
    // trafficLights.emplace_back(sf::Vector2f(350.f, 370.f)); // West
    // trafficLights.emplace_back(sf::Vector2f(450.f, 370.f)); // East

    // Initialize vehicles
    vehicles.push_back(new LightVehicle("LV1", sf::Vector2f(750.f, 360.f), sf::Vector2i(-1, 0)));
    vehicles.push_back(new HeavyVehicle("HV1", sf::Vector2f(0.f, 420.f), sf::Vector2i(1, 0)));
    vehicles.push_back(new HeavyVehicle("HV1", sf::Vector2f(420.f, 0.f), sf::Vector2i(0, 1)));
    vehicles.push_back(new EmergencyVehicle("EV1/", sf::Vector2f(150.f, 420.f), sf::Vector2i(1, 0)));
}

Simulation::~Simulation()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}

void Simulation::run()
{
    sf::Clock clock;
    

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        handleEvents();
        spawnCars(deltaTime);
        update(deltaTime);
        render();
    }
}

void Simulation::spawnCars(float deltaTime) {
    if (elapsedTime >= 5.f) {
        vehicles.push_back(new LightVehicle("LV1", sf::Vector2f(0.f, 360.f), sf::Vector2i(1, 0)));
        elapsedTime = 0.f;
    }
}

void Simulation::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Simulation::update(float deltaTime)
{
    // Update traffic lights
    for (auto &light : trafficLights)
    {
        light.update(deltaTime);
    }

    // Update vehicle positions
    for (auto vehicle : vehicles)
    {
        vehicle->updatePosition(deltaTime);
    }
}

void Simulation::render()
{
    window.clear(sf::Color::Black);

    for (const auto &road : roads)
    {
        window.draw(road.getRoadSurface());
    }
    for (const auto &road : roads)
    {
        window.draw(road.getRoadLines());
    }
    // // Draw traffic lights
    // for (const auto &light : trafficLights)
    // {
    //     window.draw(light.getShape());
    // }

    // Draw vehicles
    for (const auto vehicle : vehicles)
    {
        window.draw(vehicle->getShape());
    }


    window.display();
}
