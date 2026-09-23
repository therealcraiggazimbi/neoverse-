#include "SimulationEngine.h"
#include <iostream>
#include <iomanip>
#include <limits>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Main Application
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

void displayMainMenu();
void displayAuthMenu();
void displaySimulationMenu();
void displayAnalyticsMenu();
void handleAuthentication(SimulationEngine& engine);
void handleSimulation(SimulationEngine& engine);
void handleAnalytics(SimulationEngine& engine);

int main() {
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "                NeoVerse AI City Survival System\n";
    std::cout << "                  Advanced City Management Engine\n";
    std::cout << "                   Student: Craig GAZIMBI\n";
    std::cout << "                  Student ID: 402417962\n";
    std::cout << std::string(80, '=') << "\n";

    SimulationEngine engine;

    int mainChoice = 0;
    bool running = true;

    while (running) {
        displayMainMenu();
        std::cout << "\nEnter selection: ";
        std::cin >> mainChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (mainChoice) {
            case 1:
                handleAuthentication(engine);
                break;
            case 2:
                if (engine.getCurrentUser() != nullptr) {
                    handleSimulation(engine);
                } else {
                    std::cout << "\n[ERROR] You must authenticate first.\n";
                }
                break;
            case 3:
                if (engine.getCurrentUser() != nullptr) {
                    handleAnalytics(engine);
                } else {
                    std::cout << "\n[ERROR] You must authenticate first.\n";
                }
                break;
            case 4:
                std::cout << "\n[LOGOUT] Exiting NeoVerse System...\n";
                engine.logout();
                running = false;
                break;
            default:
                std::cout << "\n[ERROR] Invalid selection. Please try again.\n";
        }
    }

    std::cout << "\nThank you for using NeoVerse AI City Survival System.\n";
    std::cout << std::string(80, '=') << "\n\n";

    return 0;
}

void displayMainMenu() {
    std::cout << "\n" << std::string(70, '-') << "\n";
    std::cout << "                      MAIN MENU\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << "1. Authentication & Access Control\n";
    std::cout << "2. Simulation & Event Processing\n";
    std::cout << "3. Analytics & Performance Report\n";
    std::cout << "4. Exit System\n";
    std::cout << std::string(70, '-') << "\n";
}

void displayAuthMenu() {
    std::cout << "\n" << std::string(70, '-') << "\n";
    std::cout << "                AUTHENTICATION MENU\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << "1. Login Engineer\n";
    std::cout << "2. Register New Engineer\n";
    std::cout << "3. Display All Engineers\n";
    std::cout << "4. Logout\n";
    std::cout << "5. Back to Main Menu\n";
    std::cout << std::string(70, '-') << "\n";
}

void displaySimulationMenu() {
    std::cout << "\n" << std::string(70, '-') << "\n";
    std::cout << "                SIMULATION MENU\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << "1. Run Simulation (50 events)\n";
    std::cout << "2. Add Manual Event\n";
    std::cout << "3. Add Sensor Reading\n";
    std::cout << "4. Display All Subsystem Status\n";
    std::cout << "5. Process Next Event\n";
    std::cout << "6. View Simulation Status\n";
    std::cout << "7. Reset Simulation\n";
    std::cout << "8. Back to Main Menu\n";
    std::cout << std::string(70, '-') << "\n";
}

void displayAnalyticsMenu() {
    std::cout << "\n" << std::string(70, '-') << "\n";
    std::cout << "                ANALYTICS MENU\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << "1. Display Performance Report\n";
    std::cout << "2. View Recent Sensor Data\n";
    std::cout << "3. View Historical Logs\n";
    std::cout << "4. Sort Sensor Readings by Energy\n";
    std::cout << "5. Find Peak Traffic Density\n";
    std::cout << "6. Find Lowest Energy Usage\n";
    std::cout << "7. Count Critical Events\n";
    std::cout << "8. Export Data to CSV\n";
    std::cout << "9. Back to Main Menu\n";
    std::cout << std::string(70, '-') << "\n";
}

void handleAuthentication(SimulationEngine& engine) {
    int authChoice = 0;
    bool inAuthMenu = true;

    while (inAuthMenu) {
        displayAuthMenu();
        std::cout << "\nEnter selection: ";
        std::cin >> authChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (authChoice) {
            case 1: {
                std::cout << "\n--- Engineer Login ---\n";
                std::string username, password;
                std::cout << "Username: ";
                std::getline(std::cin, username);
                std::cout << "Password: ";
                std::getline(std::cin, password);

                if (engine.authenticateEngineer(username, password)) {
                    Engineer* user = engine.getCurrentUser();
                    std::cout << "\n[SUCCESS] Authentication successful!\n";
                    std::cout << "Engineer ID: " << user->getEngineerID() << "\n";
                    std::cout << "Clearance Level: " << user->getClearanceLevelString() << "\n";
                } else {
                    std::cout << "\n[FAILED] Authentication unsuccessful. Invalid credentials.\n";
                }
                break;
            }
            case 2: {
                std::cout << "\n--- Register New Engineer ---\n";
                std::string id, user, password;
                int level;

                std::cout << "Engineer ID (e.g., ENG100): ";
                std::getline(std::cin, id);
                std::cout << "Username: ";
                std::getline(std::cin, user);
                std::cout << "Password: ";
                std::getline(std::cin, password);
                std::cout << "Clearance Level (0=Low, 1=Medium, 2=High): ";
                std::cin >> level;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                ClearanceLevel cl = (level == 0) ? ClearanceLevel::Low :
                                   (level == 1) ? ClearanceLevel::Medium :
                                   ClearanceLevel::High;

                if (engine.registerEngineer(id, user, password, cl)) {
                    std::cout << "\n[SUCCESS] Engineer registered successfully.\n";
                } else {
                    std::cout << "\n[FAILED] Engineer ID already exists.\n";
                }
                break;
            }
            case 3: {
                std::cout << "\n--- Registered Engineers ---\n";
                std::cout << std::left << std::setw(12) << "Engineer ID"
                          << " | " << std::setw(15) << "Username"
                          << " | " << std::setw(8) << "Clearance"
                          << " | Status\n";
                std::cout << std::string(60, '-') << "\n";
                std::cout << "Use authentication to view engineer details.\n";
                break;
            }
            case 4: {
                engine.logout();
                std::cout << "\n[LOGOUT] Current user logged out.\n";
                break;
            }
            case 5: {
                inAuthMenu = false;
                break;
            }
            default:
                std::cout << "\n[ERROR] Invalid selection.\n";
        }
    }
}

void handleSimulation(SimulationEngine& engine) {
    int simChoice = 0;
    bool inSimMenu = true;

    while (inSimMenu) {
        displaySimulationMenu();
        std::cout << "\nEnter selection: ";
        std::cin >> simChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (simChoice) {
            case 1: {
                std::cout << "\n[SIMULATION] Running full simulation with 50 events...\n";
                engine.runSimulation(50);
                std::cout << "\n[COMPLETE] Simulation finished.\n";
                break;
            }
            case 2: {
                std::cout << "\n--- Add Manual Event ---\n";
                int type, priority;
                std::string description;

                std::cout << "Event Type (0=Traffic, 1=Power, 2=Network, 3=Weather, 4=Population, 5=Security): ";
                std::cin >> type;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Priority (0=Low, 1=Medium, 2=High, 3=Critical): ";
                std::cin >> priority;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Description: ";
                std::getline(std::cin, description);

                EventType et = static_cast<EventType>(type % 6);
                EventPriority ep = static_cast<EventPriority>(priority % 4);

                Event e(engine.getEventQueueSize() + 1, et, ep, description, "2026-09-23 12:00:00");
                engine.enqueueEvent(e);
                std::cout << "\n[EVENT] Enqueued successfully.\n";
                break;
            }
            case 3: {
                std::cout << "\n--- Add Sensor Reading ---\n";
                std::cout << "Energy Usage (MW): ";
                double energy;
                std::cin >> energy;

                std::cout << "Traffic Density (%): ";
                double traffic;
                std::cin >> traffic;

                std::cout << "Population Count: ";
                int pop;
                std::cin >> pop;

                std::cout << "Network Load (%): ";
                double network;
                std::cin >> network;

                std::cout << "Health Alerts: ";
                int health;
                std::cin >> health;

                std::cout << "Security Incidents: ";
                int security;
                std::cin >> security;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                SensorReading sr("2026-09-23 12:00:00", energy, traffic, pop, network, health, security);
                engine.addSensorReading(sr);
                std::cout << "\n[SENSOR] Reading added successfully.\n";
                break;
            }
            case 4: {
                engine.displayAllSubsystemStatus();
                break;
            }
            case 5: {
                if (!engine.isEventQueueEmpty()) {
                    engine.processNextEvent();
                } else {
                    std::cout << "\n[INFO] Event queue is empty.\n";
                }
                break;
            }
            case 6: {
                engine.displaySimulationStatus();
                break;
            }
            case 7: {
                engine.resetSimulation();
                break;
            }
            case 8: {
                inSimMenu = false;
                break;
            }
            default:
                std::cout << "\n[ERROR] Invalid selection.\n";
        }
    }
}

void handleAnalytics(SimulationEngine& engine) {
    int analyticsChoice = 0;
    bool inAnalyticsMenu = true;

    while (inAnalyticsMenu) {
        displayAnalyticsMenu();
        std::cout << "\nEnter selection: ";
        std::cin >> analyticsChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (analyticsChoice) {
            case 1: {
                engine.displayPerformanceReport();
                break;
            }
            case 2: {
                std::cout << "\nHow many recent readings to display? ";
                int count;
                std::cin >> count;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                engine.displayRecentSensorData(count);
                break;
            }
            case 3: {
                std::cout << "\nHow many recent logs to display? ";
                int count;
                std::cin >> count;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                engine.displayRecentLogs(count);
                break;
            }
            case 4: {
                std::cout << "\n[ALGORITHM] Sorting sensor readings by energy usage (std::sort)...\n";
                engine.sortSensorReadingsByEnergyUsage();
                std::cout << "[COMPLETE] Sorted in O(n log n) complexity.\n";
                break;
            }
            case 5: {
                SensorReading* maxTraffic = engine.findReadingWithHighestTrafficDensity();
                if (maxTraffic != nullptr) {
                    std::cout << "\n[PEAK TRAFFIC] Found via std::max_element (O(n)):\n";
                    maxTraffic->display();
                } else {
                    std::cout << "\n[INFO] No sensor readings available.\n";
                }
                break;
            }
            case 6: {
                SensorReading* minEnergy = engine.findReadingWithLowestEnergyUsage();
                if (minEnergy != nullptr) {
                    std::cout << "\n[MINIMUM ENERGY] Found via std::min_element (O(n)):\n";
                    minEnergy->display();
                } else {
                    std::cout << "\n[INFO] No sensor readings available.\n";
                }
                break;
            }
            case 7: {
                int criticalCount = engine.countCriticalEvents();
                std::cout << "\n[CRITICAL EVENTS] Count via std::count_if (O(n)): "
                          << criticalCount << "\n";
                break;
            }
            case 8: {
                std::cout << "\n--- Exporting Data to CSV ---\n";
                engine.exportSensorReadingsToCSV("neoverse_sensors.csv");
                engine.exportCityLogsToCSV("neoverse_logs.csv");
                engine.exportMetricsToCSV("neoverse_metrics.csv");
                std::cout << "[SUCCESS] Exported to:\n";
                std::cout << "  - neoverse_sensors.csv\n";
                std::cout << "  - neoverse_logs.csv\n";
                std::cout << "  - neoverse_metrics.csv\n";
                break;
            }
            case 9: {
                inAnalyticsMenu = false;
                break;
            }
            default:
                std::cout << "\n[ERROR] Invalid selection.\n";
        }
    }
}