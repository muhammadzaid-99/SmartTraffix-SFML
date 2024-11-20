#include "Simulation.h"
#include <random>
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
    
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.f, 0.f, 1.0, LightVehicle("LTV", sf::Vector2f(420.f, 0.f), sf::Vector2i(0, 1))});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, LightVehicle("LTV", sf::Vector2f(360.f, 760.f), sf::Vector2i(0, -1))}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.5f, 0.f, 1.0,LightVehicle("LTV", sf::Vector2f(0.f, 360.f), sf::Vector2i(1, 0))}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, LightVehicle("LTV", sf::Vector2f(760.f, 420.f), sf::Vector2i(-1, 0))}); // from west
    

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 0.2f, EmergencyVehicle("EV", sf::Vector2f(420.f, 0.f), sf::Vector2i(0, 1))});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.05f, EmergencyVehicle("EV", sf::Vector2f(360.f, 760.f), sf::Vector2i(0, -1))}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{20.f, 0.f, 0.1f, EmergencyVehicle("EV", sf::Vector2f(0.f, 360.f), sf::Vector2i(1, 0))}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.3f, EmergencyVehicle("EV", sf::Vector2f(760.f, 420.f), sf::Vector2i(-1, 0))}); // from west

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, HeavyVehicle("HTV", sf::Vector2f(470.f, 0.f), sf::Vector2i(0, 1))});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, HeavyVehicle("HTV", sf::Vector2f(310.f, 760.f), sf::Vector2i(0, -1))}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, HeavyVehicle("HTV", sf::Vector2f(0.f, 310.f), sf::Vector2i(1, 0))}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, HeavyVehicle("HTV", sf::Vector2f(760.f, 470.f), sf::Vector2i(-1, 0))}); // from west
}

Simulation::~Simulation()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}

void Simulation::addVehicle(const Vehicle& vehicle)
{
    vehicles.push_back(new Vehicle(vehicle));
}

void Simulation::run()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        handleEvents();
        spawnVehicles(deltaTime);
        update(deltaTime);
        render();
    }
}

void Simulation::spawnVehicles(float deltaTime)
{

    for (auto &timer : vehicleSpawnTimers)
    {
        timer.elapsed += deltaTime;
        float prob = pg.getRandomProb();
        std::cout << prob << std::endl;

        if (timer.elapsed >= timer.interval) {
            timer.elapsed -= timer.interval;
            if (prob <= timer.probability)
                addVehicle(timer.vehicle);
        }
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
