#include "Simulation.h"

Simulation::Simulation(unsigned int screenWidth) : window(sf::VideoMode(screenWidth, screenWidth), "SmartTraffix"), elapsedTime(0.f)
{
    unsigned sW = screenWidth;
    // Initialize roads cross-section
    roads[RoadEdge::EAST] = new Road(sf::Vector2f(0.f, sW / 2.f - 105), false, sf::Vector2i(1, 0));
    roads[RoadEdge::WEST] = new Road(sf::Vector2f(0.f, sW / 2.f + 5), false, sf::Vector2i(-1, 0));
    roads[RoadEdge::NORTH] = new Road(sf::Vector2f(sW / 2.f + 5, 0.f), true, sf::Vector2i(0, 1));
    roads[RoadEdge::SOUTH] = new Road(sf::Vector2f(sW / 2.f - 105, 0.f), true, sf::Vector2i(0, -1));

    // Initialize traffic lights
    // trafficLights.emplace_back(sf::Vector2f(370.f, 350.f)); // North
    // trafficLights.emplace_back(sf::Vector2f(370.f, 450.f)); // South
    // trafficLights.emplace_back(sf::Vector2f(350.f, 370.f)); // West
    // trafficLights.emplace_back(sf::Vector2f(450.f, 370.f)); // East

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.f, 0.f, 1.0, RoadEdge::NORTH, VehicleType::LTV}); // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, RoadEdge::SOUTH, VehicleType::LTV}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.5f, 0.f, 1.0, RoadEdge::EAST, VehicleType::LTV}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, RoadEdge::WEST, VehicleType::LTV});  // from west

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 0.2f, RoadEdge::NORTH, VehicleType::EV});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.05f, RoadEdge::SOUTH, VehicleType::EV}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{20.f, 0.f, 0.1f, RoadEdge::EAST, VehicleType::EV}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.3f, RoadEdge::WEST, VehicleType::EV}); // from west

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::NORTH, VehicleType::HTV});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::SOUTH, VehicleType::HTV}); // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::EAST, VehicleType::HTV}); // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::WEST, VehicleType::HTV}); // from west
}

Simulation::~Simulation()
{
    for (auto vehicle : vehicles)
    {
        delete vehicle;
    }
}

void Simulation::addVehicle(RoadEdge roadEdge, VehicleType vehicleType, std::string numberPlate)
{
    // vehicles.push_back(new Vehicle(vehicle));
    roads[roadEdge]->addVehicle(numberPlate, vehicleType);
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

        if (timer.elapsed >= timer.interval)
        {
            timer.elapsed -= timer.interval;
            if (prob <= timer.probability)
                addVehicle(timer.roadEdge, timer.vehicleType, "PlateNumber-N/A");
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
    // for (auto vehicle : vehicles)
    // {
    //     vehicle->updatePosition(deltaTime);
    // }

    for (const auto &road : roads)
    {
        for (const auto &flv : road.second->getFastLaneVehicles())
        {
            flv->updatePosition(deltaTime);
        }
        for (const auto &slv : road.second->getSlowLaneVehicles())
        {
            slv->updatePosition(deltaTime);
        }
    }
}

void Simulation::render()
{
    window.clear(sf::Color::Black);

    for (const auto &road : roads)
    {
        window.draw(road.second->getRoadSurface());
    }
    for (const auto &road : roads)
    {
        for (const auto &flv : road.second->getFastLaneVehicles())
        {
            window.draw(flv->getShape());
        }
        for (const auto &slv : road.second->getSlowLaneVehicles())
        {
            window.draw(slv->getShape());
        }
        window.draw(road.second->getRoadLines());
    }

    // // Draw traffic lights
    // for (const auto &light : trafficLights)
    // {
    //     window.draw(light.getShape());
    // }

    // Draw vehicles
    // for (const auto vehicle : vehicles)
    // {
    //     window.draw(vehicle->getShape());
    // }

    window.display();
}
