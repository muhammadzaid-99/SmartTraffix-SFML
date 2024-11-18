#include "Simulation.h"
Simulation::Simulation() : window(sf::VideoMode(800, 800), "SmartTraffix"), elapsedTime(0.f)
{
    // Initialize roads cross-section
    roads.emplace_back(sf::Vector2f(0.f, 345.f), false);
    roads.emplace_back(sf::Vector2f(0.f, 405.f), false);
    roads.emplace_back(sf::Vector2f(345.f, 0.f), true); 
    roads.emplace_back(sf::Vector2f(405.f, 0.f), true); 

    // Initialize traffic lights
    trafficLights.emplace_back(sf::Vector2f(370.f, 350.f)); // North
    trafficLights.emplace_back(sf::Vector2f(370.f, 450.f)); // South
    trafficLights.emplace_back(sf::Vector2f(350.f, 370.f)); // West
    trafficLights.emplace_back(sf::Vector2f(450.f, 370.f)); // East

    // Initialize vehicles
    vehicles.push_back(new LightVehicle("LV1", sf::Vector2f(0.f, 360.f)));
    vehicles.push_back(new HeavyVehicle("HV1", sf::Vector2f(0.f, 420.f)));
    vehicles.push_back(new EmergencyVehicle("EV1", sf::Vector2f(150.f, 420.f)));
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
        update(deltaTime);
        render();
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
        window.draw(road.getShape());
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
