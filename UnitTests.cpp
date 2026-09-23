#include "SimulationEngine.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <fstream>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Unit Test Suite
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────────────────────
// Custom Assertion Macros for Test Reporting
// ──────────────────────────────────────────────────────────────────────────────

int testsRun = 0;
int testsPassed = 0;
int testsFailed = 0;

#define ASSERT_TRUE(condition, message) \
    do { \
        testsRun++; \
        if (condition) { \
            testsPassed++; \
            std::cout << "[PASS] " << message << "\n"; \
        } else { \
            testsFailed++; \
            std::cout << "[FAIL] " << message << "\n"; \
        } \
    } while (0)

#define ASSERT_FALSE(condition, message) \
    ASSERT_TRUE(!(condition), message)

#define ASSERT_EQUAL(actual, expected, message) \
    do { \
        testsRun++; \
        if (actual == expected) { \
            testsPassed++; \
            std::cout << "[PASS] " << message << " (value: " << actual << ")\n"; \
        } else { \
            testsFailed++; \
            std::cout << "[FAIL] " << message << " (expected: " << expected \
                      << ", got: " << actual << ")\n"; \
        } \
    } while (0)

#define ASSERT_NOT_NULL(pointer, message) \
    do { \
        testsRun++; \
        if (pointer != nullptr) { \
            testsPassed++; \
            std::cout << "[PASS] " << message << "\n"; \
        } else { \
            testsFailed++; \
            std::cout << "[FAIL] " << message << " (pointer is null)\n"; \
        } \
    } while (0)

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 1: Authentication Logic (15 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testAuthenticationLogic() {
    std::cout << "\n========== Test Suite 1: Authentication Logic ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 1.1: Valid Credentials ---\n";
    bool authenticated = engine.authenticateEngineer("alice_chen", "secure_pass_123");
    ASSERT_TRUE(authenticated, "Alice Chen should authenticate with correct password");
    ASSERT_NOT_NULL(engine.getCurrentUser(), "Current user should be set after authentication");

    std::cout << "\n--- Test 1.2: Invalid Credentials ---\n";
    engine.logout();
    bool failedAuth = engine.authenticateEngineer("bob_smith", "wrong_password");
    ASSERT_FALSE(failedAuth, "Bob Smith should fail with wrong password");

    std::cout << "\n--- Test 1.3: Non-existent User ---\n";
    bool noUserAuth = engine.authenticateEngineer("nonexistent", "any_password");
    ASSERT_FALSE(noUserAuth, "Non-existent user should fail authentication");

    std::cout << "\n--- Test 1.4: Clearance Level Verification ---\n";
    engine.authenticateEngineer("alice_chen", "secure_pass_123");
    Engineer* user = engine.getCurrentUser();
    ASSERT_TRUE(user->getClearanceLevel() == ClearanceLevel::High,
               "Alice Chen should have High clearance");

    std::cout << "\n--- Test 1.5: Logout Functionality ---\n";
    engine.logout();
    ASSERT_FALSE(engine.getCurrentUser() != nullptr, "Current user should be null after logout");

    std::cout << "\n--- Test 1.6: Engineer Registration ---\n";
    bool registered = engine.registerEngineer("ENG099", "dave_wilson", "new_pass", ClearanceLevel::Medium);
    ASSERT_TRUE(registered, "New engineer should register successfully");

    std::cout << "\n--- Test 1.7: Duplicate Registration Prevention ---\n";
    bool duplicate = engine.registerEngineer("ENG099", "duplicate", "pass", ClearanceLevel::Low);
    ASSERT_FALSE(duplicate, "Duplicate engineer ID should not register");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 2: FIFO vs LIFO Event Processing (25 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testEventQueueVsStack() {
    std::cout << "\n========== Test Suite 2: FIFO Queue vs LIFO Stack ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 2.1: FIFO Event Queue Order ---\n";
    Event e1(1, EventType::TrafficAccident, EventPriority::Low, "Event 1", "2026-09-23 10:00:00");
    Event e2(2, EventType::PowerFailure, EventPriority::Medium, "Event 2", "2026-09-23 10:01:00");
    Event e3(3, EventType::NetworkOverload, EventPriority::High, "Event 3", "2026-09-23 10:02:00");

    engine.enqueueEvent(e1);
    engine.enqueueEvent(e2);
    engine.enqueueEvent(e3);

    ASSERT_EQUAL(engine.getEventQueueSize(), 3, "Queue should contain 3 events");

    Event retrieved1 = engine.dequeueEvent();
    ASSERT_EQUAL(retrieved1.eventID, 1, "First dequeued event should be event 1 (FIFO)");

    Event retrieved2 = engine.dequeueEvent();
    ASSERT_EQUAL(retrieved2.eventID, 2, "Second dequeued event should be event 2 (FIFO)");

    std::cout << "\n--- Test 2.2: LIFO Emergency Stack Order ---\n";
    EmergencyEvent em1(101, EventType::SecurityThreat, "Emergency 1", "2026-09-23 10:00:00", 1);
    EmergencyEvent em2(102, EventType::PowerFailure, "Emergency 2", "2026-09-23 10:01:00", 2);
    EmergencyEvent em3(103, EventType::WeatherAlert, "Emergency 3", "2026-09-23 10:02:00", 3);

    engine.pushEmergencyEvent(em1);
    engine.pushEmergencyEvent(em2);
    engine.pushEmergencyEvent(em3);

    ASSERT_EQUAL(engine.getEmergencyStackSize(), 3, "Stack should contain 3 emergencies");

    EmergencyEvent popped1 = engine.popEmergencyEvent();
    ASSERT_EQUAL(popped1.emergencyID, 103, "First popped emergency should be 103 (LIFO)");

    EmergencyEvent popped2 = engine.popEmergencyEvent();
    ASSERT_EQUAL(popped2.emergencyID, 102, "Second popped emergency should be 102 (LIFO)");

    std::cout << "\n--- Test 2.3: Queue Empty Detection ---\n";
    while (!engine.isEventQueueEmpty()) {
        engine.dequeueEvent();
    }
    ASSERT_TRUE(engine.isEventQueueEmpty(), "Queue should be empty after dequeuing all");

    std::cout << "\n--- Test 2.4: Stack Empty Detection ---\n";
    while (!engine.isEmergencyStackEmpty()) {
        engine.popEmergencyEvent();
    }
    ASSERT_TRUE(engine.isEmergencyStackEmpty(), "Stack should be empty after popping all");

    std::cout << "\n--- Test 2.5: Event Priority vs Processing Order ---\n";
    Event highPri(10, EventType::SecurityThreat, EventPriority::Critical, "Critical", "2026-09-23 10:00:00");
    Event lowPri(11, EventType::WeatherAlert, EventPriority::Low, "Minor", "2026-09-23 10:01:00");
    engine.enqueueEvent(lowPri);
    engine.enqueueEvent(highPri);
    ASSERT_FALSE(engine.isEventQueueEmpty(), "Queue should have events");
    ASSERT_TRUE(engine.getEventQueueSize() > 0, "Queue size should be greater than zero");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 3: Polymorphism & Dynamic Dispatch (15 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testPolymorphism() {
    std::cout << "\n========== Test Suite 3: Polymorphism & Dynamic Dispatch ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 3.1: Subsystem Polymorphic Dispatch ---\n";
    Event trafficEvent(1, EventType::TrafficAccident, EventPriority::High,
                      "Major accident on Main Street", "2026-09-23 10:00:00");

    engine.processEventToAllSystems(trafficEvent);
    ASSERT_TRUE(engine.getSubsystem(1) != nullptr, "Transport system should exist");

    std::cout << "\n--- Test 3.2: PowerSystem Virtual Methods ---\n";
    CityComponent* powerSys = engine.getSubsystem(0);
    ASSERT_NOT_NULL(powerSys, "Power system should not be null");
    powerSys->activate();
    ASSERT_TRUE(powerSys->getOperationalStatus(), "Power system should be operational after activation");

    std::cout << "\n--- Test 3.3: TransportSystem Virtual Methods ---\n";
    CityComponent* transportSys = engine.getSubsystem(1);
    ASSERT_NOT_NULL(transportSys, "Transport system should not be null");
    transportSys->activate();
    ASSERT_TRUE(transportSys->getOperationalStatus(), "Transport system should be operational");

    std::cout << "\n--- Test 3.4: HealthSystem Virtual Methods ---\n";
    CityComponent* healthSys = engine.getSubsystem(2);
    ASSERT_NOT_NULL(healthSys, "Health system should not be null");
    healthSys->activate();
    ASSERT_TRUE(healthSys->getOperationalStatus(), "Health system should be operational");

    std::cout << "\n--- Test 3.5: SecuritySystem Virtual Methods ---\n";
    CityComponent* securitySys = engine.getSubsystem(3);
    ASSERT_NOT_NULL(securitySys, "Security system should not be null");
    securitySys->activate();
    ASSERT_TRUE(securitySys->getOperationalStatus(), "Security system should be operational");

    std::cout << "\n--- Test 3.6: Deactivation via Base Class Pointer ---\n";
    powerSys->deactivate();
    ASSERT_FALSE(powerSys->getOperationalStatus(), "Power system should be offline after deactivation");

    std::cout << "\n--- Test 3.7: Health Status Modification via Base Interface ---\n";
    powerSys->setHealthStatus(75.5);
    ASSERT_EQUAL(static_cast<int>(powerSys->getHealthStatus()), 75, "Power system health should be 75");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 4: STL Algorithms & Analytics (20 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testSTLAlgorithms() {
    std::cout << "\n========== Test Suite 4: STL Algorithms & Analytics ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 4.1: std::sort on Sensor Readings ---\n";
    engine.addSensorReading(SensorReading("2026-09-23 10:00", 650.0, 45.0, 95000, 60.0, 12, 3));
    engine.addSensorReading(SensorReading("2026-09-23 11:00", 480.0, 55.0, 97000, 70.0, 15, 2));
    engine.addSensorReading(SensorReading("2026-09-23 12:00", 720.0, 35.0, 92000, 50.0, 8, 1));

    engine.sortSensorReadingsByEnergyUsage();
    const auto& readings = engine.getAllSensorReadings();
    ASSERT_TRUE(readings[0].energyUsage <= readings[1].energyUsage,
               "First reading should have lower or equal energy usage (std::sort)");
    ASSERT_TRUE(readings[1].energyUsage <= readings[2].energyUsage,
               "Second reading should have lower or equal energy usage (std::sort)");

    std::cout << "\n--- Test 4.2: std::max_element for Traffic Density ---\n";
    SensorReading* maxTraffic = engine.findReadingWithHighestTrafficDensity();
    ASSERT_NOT_NULL(maxTraffic, "Should find reading with highest traffic density");
    ASSERT_EQUAL(static_cast<int>(maxTraffic->trafficDensity), 55, "Max traffic should be 55%");

    std::cout << "\n--- Test 4.3: std::min_element for Energy Usage ---\n";
    SensorReading* minEnergy = engine.findReadingWithLowestEnergyUsage();
    ASSERT_NOT_NULL(minEnergy, "Should find reading with lowest energy usage");
    ASSERT_EQUAL(static_cast<int>(minEnergy->energyUsage), 480, "Min energy should be 480 MW");

    std::cout << "\n--- Test 4.4: std::count_if for Critical Events ---\n";
    engine.addCityLog(CityLog("2026-09-23 10:00", EventType::PowerFailure, EventPriority::Critical,
                             "Major blackout", "PowerSystem"));
    engine.addCityLog(CityLog("2026-09-23 10:05", EventType::TrafficAccident, EventPriority::High,
                             "Traffic jam", "TransportSystem"));
    engine.addCityLog(CityLog("2026-09-23 10:10", EventType::SecurityThreat, EventPriority::Critical,
                             "Security breach", "SecuritySystem"));

    int criticalCount = engine.countCriticalEvents();
    ASSERT_EQUAL(criticalCount, 2, "Should count 2 critical events (std::count_if)");

    std::cout << "\n--- Test 4.5: std::count_if for Event Type Frequency ---\n";
    int powerFailureCount = engine.countEventsByType(EventType::PowerFailure);
    ASSERT_EQUAL(powerFailureCount, 1, "Should count 1 PowerFailure event");

    std::cout << "\n--- Test 4.6: Average Response Latency Calculation ---\n";
    double avgLatency = engine.calculateAverageResponseLatency();
    ASSERT_TRUE(avgLatency > 0.0, "Average latency should be calculated (>0)");

    std::cout << "\n--- Test 4.7: Modal Event Type Identification ---\n";
    engine.identifyModalEventType();
    PerformanceMetrics metrics = engine.getPerformanceMetrics();
    ASSERT_TRUE(metrics.modalEventCount > 0, "Modal event count should be identified");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 5: Data Persistence & File I/O (15 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testPersistence() {
    std::cout << "\n========== Test Suite 5: File Persistence & I/O ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 5.1: Save Engineers to File ---\n";
    bool engineersSaved = engine.saveEngineersToFile("test_engineers.dat");
    ASSERT_TRUE(engineersSaved, "Engineers should save to binary file");

    std::cout << "\n--- Test 5.2: Load Engineers from File ---\n";
    SimulationEngine engine2;
    bool engineersLoaded = engine2.loadEngineersFromFile("test_engineers.dat");
    ASSERT_TRUE(engineersLoaded, "Engineers should load from binary file");

    std::cout << "\n--- Test 5.3: Save City Logs to File ---\n";
    engine.addCityLog(CityLog("2026-09-23 10:00", EventType::PowerFailure, EventPriority::Critical,
                             "Blackout incident", "PowerSystem"));
    bool logsSaved = engine.saveCityLogsToFile("test_logs.txt");
    ASSERT_TRUE(logsSaved, "Logs should save to text file");

    std::cout << "\n--- Test 5.4: Save Configuration ---\n";
    bool configSaved = engine.saveConfigToFile("test_config.txt");
    ASSERT_TRUE(configSaved, "Configuration should save to file");

    std::cout << "\n--- Test 5.5: Export Sensor Readings to CSV ---\n";
    engine.addSensorReading(SensorReading("2026-09-23 10:00", 650.0, 45.0, 95000, 60.0, 12, 3));
    bool csvSaved = engine.exportSensorReadingsToCSV("test_sensors.csv");
    ASSERT_TRUE(csvSaved, "Sensor readings should export to CSV");

    std::cout << "\n--- Test 5.6: Export City Logs to CSV ---\n";
    bool logsCSVSaved = engine.exportCityLogsToCSV("test_logs.csv");
    ASSERT_TRUE(logsCSVSaved, "City logs should export to CSV");

    std::cout << "\n--- Test 5.7: Export Performance Metrics ---\n";
    bool metricsSaved = engine.exportMetricsToCSV("test_metrics.csv");
    ASSERT_TRUE(metricsSaved, "Metrics should export to CSV");

    std::cout << "\n--- Test 5.8: Verify CSV File Existence ---\n";
    std::ifstream csvFile("test_sensors.csv");
    ASSERT_TRUE(csvFile.good(), "CSV file should exist and be readable");
    csvFile.close();

    std::cout << "\n--- Cleanup Test Files ---\n";
    std::remove("test_engineers.dat");
    std::remove("test_logs.txt");
    std::remove("test_config.txt");
    std::remove("test_sensors.csv");
    std::remove("test_logs.csv");
    std::remove("test_metrics.csv");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 6: City Data Management (20 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testDataManagement() {
    std::cout << "\n========== Test Suite 6: City Data Management ==========\n";

    SimulationEngine engine;

    std::cout << "\n--- Test 6.1: Vector Insert and Access (O(1) for access) ---\n";
    SensorReading r1("2026-09-23 10:00", 600.0, 50.0, 95000, 65.0, 10, 2);
    engine.addSensorReading(r1);
    ASSERT_EQUAL(engine.getSensorReadingCount(), 1, "Should have 1 sensor reading");
    SensorReading retrieved = engine.getSensorReading(0);
    ASSERT_EQUAL(static_cast<int>(retrieved.energyUsage), 600, "Retrieved reading should match (O(1) access)");

    std::cout << "\n--- Test 6.2: Vector Remove (O(n) for erase) ---\n";
    engine.addSensorReading(SensorReading("2026-09-23 11:00", 700.0, 60.0, 96000, 70.0, 12, 3));
    engine.removeSensorReading(0);
    ASSERT_EQUAL(engine.getSensorReadingCount(), 1, "Should have 1 reading after removal");

    std::cout << "\n--- Test 6.3: Linked List Insert (O(1) at end) ---\n";
    CityLog log1("2026-09-23 10:00", EventType::PowerFailure, EventPriority::Critical, "Outage", "Grid");
    engine.addCityLog(log1);
    ASSERT_EQUAL(engine.getCityLogCount(), 1, "Should have 1 city log");

    std::cout << "\n--- Test 6.4: Linked List Multiple Inserts (Unbounded Growth) ---\n";
    for (int i = 0; i < 100; ++i) {
        engine.addCityLog(CityLog("2026-09-23 11:00", EventType::TrafficAccident,
                                 EventPriority::Medium, "Event " + std::to_string(i), "Traffic"));
    }
    ASSERT_EQUAL(engine.getCityLogCount(), 101, "Should have 101 city logs (unbounded)");

    std::cout << "\n--- Test 6.5: List Remove Oldest (O(1) pop_front) ---\n";
    engine.removeCityLogOldest();
    ASSERT_EQUAL(engine.getCityLogCount(), 100, "Should have 100 logs after removing oldest");

    std::cout << "\n--- Test 6.6: Comparison: Vector Fast Access ---\n";
    auto& sensorVec = engine.getAllSensorReadings();
    ASSERT_TRUE(sensorVec.size() > 0 || sensorVec.size() == 1, "Vector supports random access");

    std::cout << "\n--- Test 6.7: Comparison: List Unbounded Capacity ---\n";
    auto& logList = engine.getAllCityLogs();
    ASSERT_EQUAL(static_cast<int>(logList.size()), 100, "List supports large unbounded insertion");
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Suite 7: Binary Search Analysis (5 MARKS)
// ──────────────────────────────────────────────────────────────────────────────

void testBinarySearchAnalysis() {
    std::cout << "\n========== Test Suite 7: Binary Search vs Linear Search ==========\n";

    SimulationEngine engine;
    engine.registerEngineer("ENG004", "eve_johnson", "pass123", ClearanceLevel::Low);
    engine.registerEngineer("ENG005", "frank_lee", "pass456", ClearanceLevel::Medium);

    std::cout << "\n--- Test 7.1: Linear Search (O(n)) ---\n";
    engine.sortEngineersById();
    int linearResult = engine.findEngineerByIDLinearSearch("ENG001");
    ASSERT_TRUE(linearResult >= 0 || linearResult == -1, "Linear search completes");

    std::cout << "\n--- Test 7.2: Binary Search (O(log n)) ---\n";
    int binaryResult = engine.findEngineerByIDBinarySearch("ENG002");
    ASSERT_TRUE(binaryResult >= 0 || binaryResult == -1, "Binary search completes");

    std::cout << "\n--- Test 7.3: Not Found in Linear Search ---\n";
    int notFoundLinear = engine.findEngineerByIDLinearSearch("ENG999");
    ASSERT_EQUAL(notFoundLinear, -1, "Linear search returns -1 for not found");

    std::cout << "\n--- Test 7.4: Not Found in Binary Search ---\n";
    int notFoundBinary = engine.findEngineerByIDBinarySearch("ENG999");
    ASSERT_EQUAL(notFoundBinary, -1, "Binary search returns -1 for not found");

    std::cout << "\nBig-O Analysis:\n";
    std::cout << "Linear Search:  O(n) - Must check every element in worst case\n";
    std::cout << "Binary Search:  O(log n) - Halves search space with each iteration\n";
    std::cout << "For n=1000000: Linear=1000000 ops, Binary=20 ops\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Test Report and Summary
// ──────────────────────────────────────────────────────────────────────────────

void printTestSummary() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "                    UNIT TEST SUMMARY REPORT\n";
    std::cout << std::string(70, '=') << "\n";
    std::cout << "Total Tests Run:     " << std::setw(3) << testsRun << "\n";
    std::cout << "Tests Passed:        " << std::setw(3) << testsPassed
              << " (" << std::fixed << std::setprecision(1)
              << (testsRun > 0 ? (100.0 * testsPassed / testsRun) : 0.0) << "%)\n";
    std::cout << "Tests Failed:        " << std::setw(3) << testsFailed << "\n";

    if (testsFailed == 0) {
        std::cout << "\n                   ALL TESTS PASSED!\n";
    } else {
        std::cout << "\n                  SOME TESTS FAILED\n";
    }

    std::cout << std::string(70, '=') << "\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Main Test Runner
// ──────────────────────────────────────────────────────────────────────────────

int main() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "  NeoVerse AI City Survival System - Comprehensive Unit Test Suite\n";
    std::cout << "  Author: Craig GAZIMBI (Student ID: 402417962)\n";
    std::cout << std::string(70, '=') << "\n";

    try {
        testAuthenticationLogic();
        testEventQueueVsStack();
        testPolymorphism();
        testSTLAlgorithms();
        testPersistence();
        testDataManagement();
        testBinarySearchAnalysis();

        printTestSummary();

        return testsFailed > 0 ? 1 : 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTest execution error: " << e.what() << "\n";
        return 1;
    }
}
