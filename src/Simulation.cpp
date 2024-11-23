#include "Simulation.h"

Simulation::Simulation(unsigned int screenWidth) : window(sf::VideoMode(screenWidth, screenWidth), "SmartTraffix"), simulationElapsedTime(0.f) {
    unsigned sW = screenWidth;
    lastVehicleId = 100;
    initTexts();

    // Initialize roads cross-section
    roads[RoadEdge::EAST] = new Road(sf::Vector2f(0.f, sW / 2.f - 105), false, sf::Vector2i(1, 0));
    roads[RoadEdge::WEST] = new Road(sf::Vector2f(0.f, sW / 2.f + 5), false, sf::Vector2i(-1, 0));
    roads[RoadEdge::NORTH] = new Road(sf::Vector2f(sW / 2.f + 5, 0.f), true, sf::Vector2i(0, 1));
    roads[RoadEdge::SOUTH] = new Road(sf::Vector2f(sW / 2.f - 105, 0.f), true, sf::Vector2i(0, -1));

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.f, 0.f, 1.0, RoadEdge::NORTH, VehicleType::LTV});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, RoadEdge::SOUTH, VehicleType::LTV});  // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{1.5f, 0.f, 1.0, RoadEdge::EAST, VehicleType::LTV});  // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 1.0, RoadEdge::WEST, VehicleType::LTV});   // from west

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 0.2f, RoadEdge::NORTH, VehicleType::EV});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.05f, RoadEdge::SOUTH, VehicleType::EV});  // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{20.f, 0.f, 0.1f, RoadEdge::EAST, VehicleType::EV});   // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{2.f, 0.f, 0.3f, RoadEdge::WEST, VehicleType::EV});    // from west

    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::NORTH, VehicleType::HTV});  // from north
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::SOUTH, VehicleType::HTV});  // from south
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::EAST, VehicleType::HTV});   // from east
    vehicleSpawnTimers.push_back(VehicleSpawnTimer{15.f, 0.f, 1.f, RoadEdge::WEST, VehicleType::HTV});   // from west

    currentTimeOffset = pg.getRandomProb() * 86400;  // 86400 seconds in a day
}

Simulation::~Simulation() {
    for (auto &road : roads) {
        delete road.second;
    }
}

void Simulation::addVehicle(RoadEdge roadEdge, VehicleType vehicleType, sf::Text numberPlate) {
    // vehicles.push_back(new Vehicle(vehicle));
    roads[roadEdge]->addVehicle(numberPlate, vehicleType);
}

void Simulation::initTexts() {
    if (!font.loadFromFile("../assets/fonts/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }

    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(18);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(10.f, 10.f);
    roadLengthText.setFont(font);
    roadLengthText.setCharacterSize(18);
    roadLengthText.setFillColor(sf::Color::White);
    roadLengthText.setPosition(10.f, 30.f);
    roadLengthText.setString("Road Length: 800m, edge to edge");
    currentTimeText.setFont(font);
    currentTimeText.setCharacterSize(18);
    currentTimeText.setFillColor(sf::Color::White);
    currentTimeText.setPosition(10.f, 50.f);
}

void Simulation::run() {
    sf::Clock simulationClock;

    while (window.isOpen()) {
        float deltaTime = simulationClock.restart().asSeconds();
        simulationElapsedTime += deltaTime;
        elapsedTimeText.setString(sf::String("Elapsed Time: " + std::to_string(static_cast<int>(simulationElapsedTime))) + "s");

        handleEvents();
        spawnVehicles(deltaTime);
        update(deltaTime);
        render();
    }
}

void Simulation::spawnVehicles(float deltaTime) {
    for (auto &timer : vehicleSpawnTimers) {
        timer.elapsed += deltaTime;
        float prob = pg.getRandomProb();

        if (timer.elapsed >= timer.interval) {
            timer.elapsed -= timer.interval;
            if (prob <= timer.probability && (!(timer.vehicleType == VehicleType::HTV) || !isPeakTime))
                addVehicle(timer.roadEdge, timer.vehicleType, sf::Text(std::to_string(lastVehicleId++), font));
        }
    }
}

void Simulation::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

std::string Simulation::updatedAndGetFormattedTime(int hour, int minute, int second) {
    std::string period = (hour < 12) ? "am" : "pm";
    second += currentTimeOffset;
    if (second >= 60) {
        minute += second / 60;
        second = second % 60;
    }
    if (minute >= 60) {
        hour += minute / 60;
        minute = minute % 60;
    }
    if (hour >= 24) {
        hour = hour % 24;
    }
    hour = (hour % 12 == 0) ? 12 : hour % 12;

    if (period == "am" && hour >= 7 && (hour < 9 || (hour == 9 && minute < 30))) {
        isPeakTime = true;
    } else if (period == "pm" && (hour > 4 || (hour == 4 && minute >= 30)) && (hour < 8 || (hour == 8 && minute < 30))) {
        isPeakTime = true;
    } else {
        isPeakTime = false;
    }

    std::string hourStr = (hour < 10 ? "0" : "") + std::to_string(hour);
    std::string minuteStr = (minute < 10 ? "0" : "") + std::to_string(minute);
    std::string secondStr = (second < 10 ? "0" : "") + std::to_string(second);

    return hourStr + ":" + minuteStr + ":" + secondStr + " " + period;
}

const sf::Text &Simulation::getCurrentTimeText() {
    std::time_t now = std::time(0);
    std::tm *localTime = std::localtime(&now);
    currentTimeText.setString(updatedAndGetFormattedTime(localTime->tm_hour, localTime->tm_min, localTime->tm_sec));
    return currentTimeText;
}

void Simulation::update(float deltaTime) {
    for (const auto &road : roads) {
        for (const auto &flv : road.second->getFastLaneVehicles()) {
            flv->updatePosition(deltaTime);
        }
        for (const auto &slv : road.second->getSlowLaneVehicles()) {
            slv->updatePosition(deltaTime);
        }

        road.second->removeLeftVehicles();
        road.second->updateTrafficLight(deltaTime);

        const auto &fastLane = road.second->getFastLaneVehicles();

        // Adjust speeds to ensure safe distances
        for (auto flv_it = fastLane.begin(); flv_it != fastLane.end(); flv_it++) {
            // Leading vehicle: allow it to maintain/increase speed
            const float &elapsedTime = (*flv_it)->getElapsedTime();
            if (flv_it == fastLane.begin()) {
                if (elapsedTime >= 1.f) {
                    (*flv_it)->setElapsedTime(elapsedTime - 1.f);
                    // (*flv_it)->increaseSpeed(1.3889f * 8); // 5km/h = 1.3889m/s
                    (*flv_it)->increaseSpeed(0.27778f * 8);  // for each 1m/s increase, increase by 1km/h using vf = vi + at
                }
                continue;  // Skip further checks for the leading vehicle
            }

            // For all other vehicles, ensure safe distance with the vehicle ahead
            auto ahead_it = std::prev(flv_it);  // Vehicle ahead (closer to the front)
            if (!Vehicle::areVehiclesAtSafeDistance(**flv_it, **ahead_it)) {
                if ((*ahead_it)->getIsStopped())
                    (*flv_it)->setIsStopped(true);
                else
                    (*flv_it)->setIsStopped(false);
                // Reduce speed to maintain safe distance
                (*flv_it)->decreaseSpeed(std::abs((*ahead_it)->getSpeed() - (*flv_it)->getSpeed()));  // equal to the vehicle ahead
                // (*flv_it)->decreaseSpeed(1.3889f * 4); // Slow down by 2.5 km/h if too close
            } else if (elapsedTime >= 1.f) {
                (*flv_it)->setElapsedTime(elapsedTime - 1.f);
                // If safe, allow to increase speed
                // (*flv_it)->increaseSpeed(1.3889f * 8); // 5km/h
                (*flv_it)->increaseSpeed(0.27778f * 8);  // ncrease by 1km/h after each second
            }
        }
    }
}

void Simulation::render() {
    window.clear(sf::Color::Black);

    for (const auto &road : roads) {
        window.draw(road.second->getRoadSurface());
    }
    for (const auto &road : roads) {
        window.draw(road.second->getRoadLines());
        window.draw(road.second->getIntersectorLine());
        window.draw(road.second->getTrafficLight());
    }
    for (const auto &road : roads) {
        for (const auto &flv : road.second->getFastLaneVehicles()) {
            window.draw(flv->getShape());
            window.draw(flv->getNumberPlate());
        }
        for (const auto &slv : road.second->getSlowLaneVehicles()) {
            window.draw(slv->getShape());
            window.draw(slv->getNumberPlate());
        }
    }
    // Draw time
    window.draw(elapsedTimeText);
    window.draw(roadLengthText);
    window.draw(getCurrentTimeText());

    window.display();
}
