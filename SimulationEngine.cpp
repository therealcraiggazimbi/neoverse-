#include "SimulationEngine.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Engine Implementation
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

SimulationEngine::SimulationEngine()
    : currentUser(nullptr), eventCounter(0), emergencyCounter(0) {
    initializeDefaultEngineers();
    initializeSubsystems();
}

// ──────────────────────────────────────────────────────────────────────────────
// Authentication & Access Control Implementation
// ──────────────────────────────────────────────────────────────────────────────

bool SimulationEngine::authenticateEngineer(const std::string& username,
                                            const std::string& password) {
    auto it = std::find_if(engineers.begin(), engineers.end(),
        [&username](const Engineer& e) { return e.getUsername() == username; });

    if (it != engineers.end()) {
        if (it->authenticate(password)) {
            currentUser = &(*it);
            return true;
        }
    }
    return false;
}

bool SimulationEngine::registerEngineer(const std::string& id,
                                       const std::string& user,
                                       const std::string& password,
                                       ClearanceLevel level) {
    auto exists = std::find_if(engineers.begin(), engineers.end(),
        [&id](const Engineer& e) { return e.getEngineerID() == id; });

    if (exists == engineers.end()) {
        engineers.emplace_back(id, user, password, level);
        return true;
    }
    return false;
}

void SimulationEngine::logout() {
    if (currentUser) {
        currentUser->setAuthenticated(false);
        currentUser = nullptr;
    }
}

int SimulationEngine::findEngineerByIDLinearSearch(const std::string& id) {
    // O(n) complexity - checks every element
    for (size_t i = 0; i < engineers.size(); ++i) {
        if (engineers[i].getEngineerID() == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int SimulationEngine::findEngineerByIDBinarySearch(const std::string& id) {
    // O(log n) complexity - requires sorted array by ID
    // Note: this requires engineers sorted by ID first via sortEngineersById()
    int left = 0, right = static_cast<int>(engineers.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        const std::string& midID = engineers[mid].getEngineerID();

        if (midID == id) {
            return mid;
        } else if (midID < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void SimulationEngine::sortEngineersById() {
    std::sort(engineers.begin(), engineers.end(),
        [](const Engineer& a, const Engineer& b) {
            return a.getEngineerID() < b.getEngineerID();
        });
}

// ──────────────────────────────────────────────────────────────────────────────
// City Data Management Implementation
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::addSensorReading(const SensorReading& reading) {
    sensorReadings.push_back(reading);
}

void SimulationEngine::removeSensorReading(size_t index) {
    if (index < sensorReadings.size()) {
        sensorReadings.erase(sensorReadings.begin() + index);
    }
}

SensorReading SimulationEngine::getSensorReading(size_t index) const {
    if (index < sensorReadings.size()) {
        return sensorReadings[index];
    }
    return SensorReading();
}

const std::vector<SensorReading>& SimulationEngine::getAllSensorReadings() const {
    return sensorReadings;
}

void SimulationEngine::addCityLog(const CityLog& log) {
    // O(1) insertion at end of linked list
    cityHistoricalLogs.push_back(log);
}

void SimulationEngine::removeCityLogOldest() {
    if (!cityHistoricalLogs.empty()) {
        cityHistoricalLogs.pop_front();
    }
}

const std::list<CityLog>& SimulationEngine::getAllCityLogs() const {
    return cityHistoricalLogs;
}

void SimulationEngine::displayRecentSensorData(int count) const {
    std::cout << "\n=== Recent Sensor Readings (Vector - O(1) Access) ===\n";
    int displayCount = std::min(count, static_cast<int>(sensorReadings.size()));
    for (int i = sensorReadings.size() - displayCount; i < static_cast<int>(sensorReadings.size()); ++i) {
        if (i >= 0) {
            sensorReadings[i].display();
        }
    }
}

void SimulationEngine::displayRecentLogs(int count) const {
    std::cout << "\n=== Recent Historical Logs (List - Unbounded) ===\n";
    int displayCount = std::min(count, static_cast<int>(cityHistoricalLogs.size()));
    auto it = cityHistoricalLogs.rbegin();
    for (int i = 0; i < displayCount && it != cityHistoricalLogs.rend(); ++i, ++it) {
        it->display();
    }
}

// ──────────────────────────────────────────────────────────────────────────────
// Event Processing Implementation (FIFO Queue)
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::enqueueEvent(const Event& event) {
    eventQueue.push(event);
}

Event SimulationEngine::dequeueEvent() {
    Event e = eventQueue.front();
    eventQueue.pop();
    return e;
}

bool SimulationEngine::isEventQueueEmpty() const {
    return eventQueue.empty();
}

int SimulationEngine::getEventQueueSize() const {
    return static_cast<int>(eventQueue.size());
}

// ──────────────────────────────────────────────────────────────────────────────
// Emergency Event Processing Implementation (LIFO Stack)
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::pushEmergencyEvent(const EmergencyEvent& emergency) {
    emergencyStack.push(emergency);
}

EmergencyEvent SimulationEngine::popEmergencyEvent() {
    EmergencyEvent e = emergencyStack.top();
    emergencyStack.pop();
    return e;
}

bool SimulationEngine::isEmergencyStackEmpty() const {
    return emergencyStack.empty();
}

int SimulationEngine::getEmergencyStackSize() const {
    return static_cast<int>(emergencyStack.size());
}

void SimulationEngine::processNextEvent() {
    if (!eventQueue.empty()) {
        Event e = dequeueEvent();
        std::cout << "\n[EVENT PROCESSED] ID: " << e.eventID
                  << " | Type: " << static_cast<int>(e.type)
                  << " | Priority: " << static_cast<int>(e.priority) << "\n";

        for (auto& subsystem : subsystems) {
            subsystem->processEvent(e);
        }

        addCityLog(CityLog(e.timestamp, e.type, e.priority,
                          e.description, "SimulationEngine"));
        eventCounter++;
        metrics.totalEventsProcessed++;
    }
}

void SimulationEngine::processNextEmergency() {
    if (!emergencyStack.empty()) {
        EmergencyEvent e = popEmergencyEvent();
        std::cout << "\n[EMERGENCY OVERRIDE] ID: " << e.emergencyID
                  << " | Priority Mask: " << e.systemsPriority << "\n";

        // Create event from emergency for subsystem processing
        Event emgEvent(e.emergencyID, e.type, EventPriority::Critical,
                      e.description, e.timestamp);
        for (auto& subsystem : subsystems) {
            subsystem->processEvent(emgEvent);
        }

        addCityLog(CityLog(e.timestamp, e.type, EventPriority::Critical,
                          "EMERGENCY: " + e.description, "EmergencyOverride"));
        emergencyCounter++;
        metrics.totalEventsProcessed++;
    }
}

void SimulationEngine::processAllEvents() {
    while (!isEmergencyStackEmpty()) {
        processNextEmergency();
    }
    while (!isEventQueueEmpty()) {
        processNextEvent();
    }
}

void SimulationEngine::filterEventsByType(EventType type) {
    std::cout << "\n=== Events of Type " << static_cast<int>(type) << " ===\n";
    // Note: std::queue does not support iteration; this is for demonstration
    std::cout << "Queue filtering requires copying queue contents\n";
}

void SimulationEngine::filterEventsByPriority(EventPriority priority) {
    std::cout << "\n=== Events with Priority " << static_cast<int>(priority) << " ===\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Subsystem Management & Polymorphism
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::initializeSubsystems() {
    subsystems.push_back(std::make_shared<PowerSystem>(1));
    subsystems.push_back(std::make_shared<TransportSystem>(2));
    subsystems.push_back(std::make_shared<HealthSystem>(3));
    subsystems.push_back(std::make_shared<SecuritySystem>(4));
}

void SimulationEngine::processEventToAllSystems(const Event& event) {
    // Dynamic polymorphism: calls virtual processEvent() on each subsystem
    for (auto& subsystem : subsystems) {
        subsystem->processEvent(event);
    }
}

void SimulationEngine::displayAllSubsystemStatus() const {
    std::cout << "\n=== City Subsystems Status ===\n";
    for (const auto& subsystem : subsystems) {
        std::cout << subsystem->getStatus() << "\n";
    }
}

CityComponent* SimulationEngine::getSubsystem(int index) {
    if (index >= 0 && index < static_cast<int>(subsystems.size())) {
        return subsystems[index].get();
    }
    return nullptr;
}

// ──────────────────────────────────────────────────────────────────────────────
// STL Algorithms & Analytics
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::sortSensorReadingsByEnergyUsage() {
    // std::sort with custom comparator - O(n log n)
    std::sort(sensorReadings.begin(), sensorReadings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.energyUsage < b.energyUsage;
        });
    std::cout << "\n[SORTED] Sensor readings by energy usage (ascending)\n";
}

SensorReading* SimulationEngine::findReadingWithHighestTrafficDensity() {
    // std::max_element - O(n)
    auto it = std::max_element(sensorReadings.begin(), sensorReadings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.trafficDensity < b.trafficDensity;
        });

    if (it != sensorReadings.end()) {
        return &(*it);
    }
    return nullptr;
}

SensorReading* SimulationEngine::findReadingWithLowestEnergyUsage() {
    // std::min_element - O(n)
    auto it = std::min_element(sensorReadings.begin(), sensorReadings.end(),
        [](const SensorReading& a, const SensorReading& b) {
            return a.energyUsage < b.energyUsage;
        });

    if (it != sensorReadings.end()) {
        return &(*it);
    }
    return nullptr;
}

int SimulationEngine::countCriticalEvents() {
    // std::count_if - O(n)
    return std::count_if(cityHistoricalLogs.begin(), cityHistoricalLogs.end(),
        [](const CityLog& log) {
            return log.priority == EventPriority::Critical;
        });
}

int SimulationEngine::countEventsByType(EventType type) {
    // std::count_if - O(n)
    return std::count_if(cityHistoricalLogs.begin(), cityHistoricalLogs.end(),
        [type](const CityLog& log) {
            return log.eventType == type;
        });
}

double SimulationEngine::calculateAverageResponseLatency() {
    if (cityHistoricalLogs.empty()) return 0.0;

    double totalLatency = 0.0;
    int count = 0;

    for (const auto& log : cityHistoricalLogs) {
        totalLatency += 5.0 + (static_cast<int>(log.priority) * 2.5);
        count++;
    }

    metrics.averageResponseLatency = totalLatency / count;
    return metrics.averageResponseLatency;
}

void SimulationEngine::identifyModalEventType() {
    if (cityHistoricalLogs.empty()) return;

    std::vector<int> eventTypeCounts(6, 0);
    for (const auto& log : cityHistoricalLogs) {
        eventTypeCounts[static_cast<int>(log.eventType)]++;
    }

    auto maxIt = std::max_element(eventTypeCounts.begin(), eventTypeCounts.end());
    metrics.modalEventType = std::distance(eventTypeCounts.begin(), maxIt);
    metrics.modalEventCount = *maxIt;
}

// ──────────────────────────────────────────────────────────────────────────────
// Persistence & File I/O
// ──────────────────────────────────────────────────────────────────────────────

bool SimulationEngine::saveEngineersToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    size_t count = engineers.size();
    file.write(reinterpret_cast<char*>(&count), sizeof(count));

    for (const auto& eng : engineers) {
        size_t idLen = eng.getEngineerID().length();
        file.write(reinterpret_cast<char*>(&idLen), sizeof(idLen));
        file.write(eng.getEngineerID().c_str(), idLen);

        size_t userLen = eng.getUsername().length();
        file.write(reinterpret_cast<char*>(&userLen), sizeof(userLen));
        file.write(eng.getUsername().c_str(), userLen);

        int level = static_cast<int>(eng.getClearanceLevel());
        file.write(reinterpret_cast<char*>(&level), sizeof(level));
    }

    file.close();
    return true;
}

bool SimulationEngine::loadEngineersFromFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    size_t count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        size_t idLen = 0;
        file.read(reinterpret_cast<char*>(&idLen), sizeof(idLen));
        std::string id(idLen, '\0');
        file.read(&id[0], idLen);

        size_t userLen = 0;
        file.read(reinterpret_cast<char*>(&userLen), sizeof(userLen));
        std::string user(userLen, '\0');
        file.read(&user[0], userLen);

        int level = 0;
        file.read(reinterpret_cast<char*>(&level), sizeof(level));

        engineers.emplace_back(id, user, "default", static_cast<ClearanceLevel>(level));
    }

    file.close();
    return true;
}

bool SimulationEngine::saveEventsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "EventID,Type,Priority,Description,Timestamp\n";
    int eventId = 1;

    for (const auto& log : cityHistoricalLogs) {
        file << eventId++ << "," << static_cast<int>(log.eventType) << ","
             << static_cast<int>(log.priority) << "," << log.description << ","
             << log.timestamp << "\n";
    }

    file.close();
    return true;
}

bool SimulationEngine::loadEventsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        // Simple CSV parsing
        // Format: EventID,Type,Priority,Description,Timestamp
    }

    file.close();
    return true;
}

bool SimulationEngine::saveCityLogsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    for (const auto& log : cityHistoricalLogs) {
        file << log.timestamp << " | " << log.getEventTypeString() << " | "
             << log.getPriorityString() << " | " << log.description << "\n";
    }

    file.close();
    return true;
}

bool SimulationEngine::loadCityLogsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    file.close();
    return true;
}

bool SimulationEngine::saveConfigToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "NeoVerse Configuration\n";
    file << "Engineers: " << engineers.size() << "\n";
    file << "Sensor Readings: " << sensorReadings.size() << "\n";
    file << "City Logs: " << cityHistoricalLogs.size() << "\n";
    file << "Subsystems: " << subsystems.size() << "\n";

    file.close();
    return true;
}

bool SimulationEngine::loadConfigFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        // Parse configuration
    }

    file.close();
    return true;
}

bool SimulationEngine::exportSensorReadingsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "Timestamp,EnergyUsage,TrafficDensity,Population,NetworkLoad,HealthAlerts,SecurityIncidents\n";

    for (const auto& reading : sensorReadings) {
        file << reading.timestamp << "," << std::fixed << std::setprecision(2)
             << reading.energyUsage << "," << reading.trafficDensity << ","
             << reading.populationCount << "," << reading.networkLoad << ","
             << reading.healthAlerts << "," << reading.securityIncidents << "\n";
    }

    file.close();
    return true;
}

bool SimulationEngine::exportCityLogsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "Timestamp,EventType,Priority,Description,SystemAffected\n";

    for (const auto& log : cityHistoricalLogs) {
        file << log.timestamp << "," << log.getEventTypeString() << ","
             << log.getPriorityString() << "," << log.description << ","
             << log.systemAffected << "\n";
    }

    file.close();
    return true;
}

bool SimulationEngine::exportMetricsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "Metric,Value\n";
    file << "Average Response Latency (ms)," << std::fixed << std::setprecision(2)
         << metrics.averageResponseLatency << "\n";
    file << "Total Events Processed," << metrics.totalEventsProcessed << "\n";
    file << "Modal Event Type," << metrics.modalEventType << "\n";
    file << "Power System Health," << metrics.powerSystemHealth << "\n";
    file << "Transport System Health," << metrics.transportSystemHealth << "\n";
    file << "Health System Health," << metrics.healthSystemHealth << "\n";
    file << "Security System Health," << metrics.securitySystemHealth << "\n";

    file.close();
    return true;
}

// ──────────────────────────────────────────────────────────────────────────────
// Simulation Control
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::runSimulation(int eventCount) {
    std::cout << "\n=== Starting NeoVerse Simulation ===\n";
    std::cout << "Processing " << eventCount << " events...\n\n";

    for (int i = 0; i < eventCount; ++i) {
        EventType types[] = { EventType::TrafficAccident, EventType::PowerFailure,
                             EventType::NetworkOverload, EventType::WeatherAlert };
        EventPriority priorities[] = { EventPriority::Low, EventPriority::Medium,
                                      EventPriority::High, EventPriority::Critical };

        Event e(i + 1, types[i % 4], priorities[i % 4],
               "Simulated event #" + std::to_string(i + 1), getTimestamp());

        enqueueEvent(e);
        if (i % 5 == 0) {
            EmergencyEvent emg(i + 1000, EventType::SecurityThreat,
                             "Emergency override #" + std::to_string(i + 1),
                             getTimestamp(), i % 4);
            pushEmergencyEvent(emg);
        }
    }

    processAllEvents();
    updateMetrics();
}

void SimulationEngine::resetSimulation() {
    while (!isEventQueueEmpty()) dequeueEvent();
    while (!isEmergencyStackEmpty()) popEmergencyEvent();
    sensorReadings.clear();
    cityHistoricalLogs.clear();
    eventCounter = 0;
    emergencyCounter = 0;
    metrics = PerformanceMetrics();
    std::cout << "\n[RESET] Simulation state cleared\n";
}

void SimulationEngine::displaySimulationStatus() const {
    std::cout << "\n=== Simulation Status ===\n";
    std::cout << "Events in Queue: " << getEventQueueSize() << "\n";
    std::cout << "Emergencies in Stack: " << getEmergencyStackSize() << "\n";
    std::cout << "Total Sensor Readings: " << getSensorReadingCount() << "\n";
    std::cout << "Total City Logs: " << getCityLogCount() << "\n";
    std::cout << "Events Processed: " << eventCounter << "\n";
    std::cout << "Emergencies Processed: " << emergencyCounter << "\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Private Helper Methods
// ──────────────────────────────────────────────────────────────────────────────

void SimulationEngine::initializeDefaultEngineers() {
    registerEngineer("ENG001", "alice_chen", "secure_pass_123", ClearanceLevel::High);
    registerEngineer("ENG002", "bob_smith", "password_456", ClearanceLevel::Medium);
    registerEngineer("ENG003", "carol_jones", "pass_789", ClearanceLevel::Low);
}

std::string SimulationEngine::getTimestamp() const {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void SimulationEngine::updateMetrics() {
    calculateAverageResponseLatency();
    identifyModalEventType();
    updateSubsystemHealthMetrics();
}

void SimulationEngine::updateSubsystemHealthMetrics() {
    if (subsystems.size() >= 4) {
        metrics.powerSystemHealth = subsystems[0]->getHealthStatus();
        metrics.transportSystemHealth = subsystems[1]->getHealthStatus();
        metrics.healthSystemHealth = subsystems[2]->getHealthStatus();
        metrics.securitySystemHealth = subsystems[3]->getHealthStatus();
    }
}

#include <sstream>
