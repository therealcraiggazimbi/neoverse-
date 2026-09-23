#pragma once

#include "Types.h"
#include "CityComponent.h"
#include "Subsystems.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
#include <memory>
#include <fstream>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Simulation Engine
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

class SimulationEngine {
private:
    // ──────────────────────────────────────────────────────────────────────
    // Authentication: Binary searchable engineer database (O(log n) lookup)
    // ──────────────────────────────────────────────────────────────────────
    std::vector<Engineer>           engineers;
    Engineer*                       currentUser;

    // ──────────────────────────────────────────────────────────────────────
    // City Data: Vector for O(1) sensor access vs List for unbounded logs
    // ──────────────────────────────────────────────────────────────────────
    std::vector<SensorReading>      sensorReadings;      // Fast random access
    std::list<CityLog>              cityHistoricalLogs;  // Unbounded growth

    // ──────────────────────────────────────────────────────────────────────
    // Event Processing: FIFO queue and LIFO emergency stack
    // ──────────────────────────────────────────────────────────────────────
    std::queue<Event>               eventQueue;          // Standard events (FIFO)
    std::stack<EmergencyEvent>      emergencyStack;      // Overrides (LIFO)

    // ──────────────────────────────────────────────────────────────────────
    // OOP Subsystems: Dynamic polymorphism via base class pointers
    // ──────────────────────────────────────────────────────────────────────
    std::vector<std::shared_ptr<CityComponent>> subsystems;

    // ──────────────────────────────────────────────────────────────────────
    // Performance tracking
    // ──────────────────────────────────────────────────────────────────────
    PerformanceMetrics              metrics;
    int                             eventCounter;
    int                             emergencyCounter;

public:
    SimulationEngine();
    virtual ~SimulationEngine() = default;

    // ──────────────────────────────────────────────────────────────────────
    // 1. AI Agent Authentication & Access Control (15 MARKS)
    // ──────────────────────────────────────────────────────────────────────

    bool authenticateEngineer(const std::string& username,
                             const std::string& password);
    bool registerEngineer(const std::string& id, const std::string& user,
                         const std::string& password, ClearanceLevel level);
    Engineer* getCurrentUser() const { return currentUser; }
    void logout();

    // Binary search vs Linear search comparison for authentication
    // Binary search: O(log n) if sorted; Linear search: O(n) always
    int findEngineerByIDLinearSearch(const std::string& id);
    int findEngineerByIDBinarySearch(const std::string& id);
    void sortEngineersById();

    // ──────────────────────────────────────────────────────────────────────
    // 2. City Data Management (20 MARKS)
    // ──────────────────────────────────────────────────────────────────────

    // Vector operations: Fast contiguous access for sensor readings
    void addSensorReading(const SensorReading& reading);
    void removeSensorReading(size_t index);
    SensorReading getSensorReading(size_t index) const;
    size_t getSensorReadingCount() const { return sensorReadings.size(); }
    const std::vector<SensorReading>& getAllSensorReadings() const;

    // List operations: Unbounded historical logs with O(1) insertion
    void addCityLog(const CityLog& log);
    void removeCityLogOldest();
    size_t getCityLogCount() const { return cityHistoricalLogs.size(); }
    const std::list<CityLog>& getAllCityLogs() const;

    // Data analysis
    void displayRecentSensorData(int count) const;
    void displayRecentLogs(int count) const;

    // ──────────────────────────────────────────────────────────────────────
    // 3. Event Processing System (25 MARKS)
    // ──────────────────────────────────────────────────────────────────────

    // FIFO Event Queue
    void enqueueEvent(const Event& event);
    Event dequeueEvent();
    bool isEventQueueEmpty() const;
    int getEventQueueSize() const;

    // LIFO Emergency Stack
    void pushEmergencyEvent(const EmergencyEvent& emergency);
    EmergencyEvent popEmergencyEvent();
    bool isEmergencyStackEmpty() const;
    int getEmergencyStackSize() const;

    // Event processing and prioritization
    void processNextEvent();
    void processNextEmergency();
    void processAllEvents();
    void filterEventsByType(EventType type);
    void filterEventsByPriority(EventPriority priority);

    // ──────────────────────────────────────────────────────────────────────
    // 4. Object-Oriented City Architecture (15 MARKS)
    // ──────────────────────────────────────────────────────────────────────

    // Subsystem management (polymorphic dispatch)
    void initializeSubsystems();
    void processEventToAllSystems(const Event& event);
    void displayAllSubsystemStatus() const;
    CityComponent* getSubsystem(int index);

    // ──────────────────────────────────────────────────────────────────────
    // STL Algorithms & Analytics
    // ──────────────────────────────────────────────────────────────────────

    // STL algorithm implementations as per specification
    void sortSensorReadingsByEnergyUsage();
    SensorReading* findReadingWithHighestTrafficDensity();
    SensorReading* findReadingWithLowestEnergyUsage();
    int countCriticalEvents();
    int countEventsByType(EventType type);
    double calculateAverageResponseLatency();
    void identifyModalEventType();

    // ──────────────────────────────────────────────────────────────────────
    // Persistence & File I/O
    // ──────────────────────────────────────────────────────────────────────

    bool saveEngineersToFile(const std::string& filename);
    bool loadEngineersFromFile(const std::string& filename);
    bool saveEventsToFile(const std::string& filename);
    bool loadEventsFromFile(const std::string& filename);
    bool saveCityLogsToFile(const std::string& filename);
    bool loadCityLogsFromFile(const std::string& filename);
    bool saveConfigToFile(const std::string& filename);
    bool loadConfigFromFile(const std::string& filename);

    // CSV export for analytics
    bool exportSensorReadingsToCSV(const std::string& filename);
    bool exportCityLogsToCSV(const std::string& filename);
    bool exportMetricsToCSV(const std::string& filename);

    // ──────────────────────────────────────────────────────────────────────
    // Analytics & Reporting
    // ──────────────────────────────────────────────────────────────────────

    PerformanceMetrics getPerformanceMetrics() const { return metrics; }
    void displayPerformanceReport() const;
    void updateSubsystemHealthMetrics();

    // Simulation control
    void runSimulation(int eventCount);
    void resetSimulation();
    void displaySimulationStatus() const;

private:
    // Helper methods
    void initializeDefaultEngineers();
    std::string getTimestamp() const;
    void updateMetrics();
};
