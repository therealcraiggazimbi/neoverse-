#include "Subsystems.h"
#include <iostream>
#include <iomanip>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Subsystems Implementation
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────────────────────
// PowerSystem Implementation
// ──────────────────────────────────────────────────────────────────────────────

void PowerSystem::processEvent(const Event& event) {
    if (event.type == EventType::PowerFailure) {
        respondToFailure(event);
    } else if (event.priority == EventPriority::Critical) {
        activateEmergencyPower();
    }
}

void PowerSystem::activate() {
    isOperational = true;
    powerLevel = maxCapacity * 0.8;
    healthStatus = 100.0;
    std::cout << "[POWER] System activated - capacity: " << powerLevel << " MW\n";
}

void PowerSystem::deactivate() {
    isOperational = false;
    powerLevel = 0.0;
    healthStatus = 0.0;
    std::cout << "[POWER] System deactivated\n";
}

std::string PowerSystem::getStatus() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "[POWER SYSTEM] Health: " << healthStatus << "% | "
        << "Level: " << powerLevel << "/" << maxCapacity << " MW | "
        << "Demand: " << currentDemand << " MW | "
        << "Substations: " << substationsActive << "/8 | "
        << (emergencyMode ? "EMERGENCY MODE" : "Normal");
    return oss.str();
}

void PowerSystem::supplyPower(double megawatts) {
    if (isOperational) {
        powerLevel = std::min(powerLevel + megawatts, maxCapacity);
    }
}

void PowerSystem::respondToFailure(const Event& event) {
    std::cout << "[POWER ALERT] Responding to: " << event.description << "\n";
    powerLevel *= 0.7;
    healthStatus -= 15.0;
    if (healthStatus < 0.0) healthStatus = 0.0;
    if (powerLevel < currentDemand * 0.5) {
        activateEmergencyPower();
    }
}

void PowerSystem::activateEmergencyPower() {
    std::cout << "[POWER] Emergency backup activated\n";
    emergencyMode = true;
    powerLevel = maxCapacity * 0.6;
    healthStatus = 75.0;
}

// ──────────────────────────────────────────────────────────────────────────────
// TransportSystem Implementation
// ──────────────────────────────────────────────────────────────────────────────

void TransportSystem::processEvent(const Event& event) {
    if (event.type == EventType::TrafficAccident) {
        respondToAccident(event);
    } else if (event.type == EventType::NetworkOverload) {
        optimizeRoutes();
    }
}

void TransportSystem::activate() {
    isOperational = true;
    trafficFlow = maxCapacity * 0.7;
    healthStatus = 100.0;
    std::cout << "[TRANSPORT] System activated - flow: " << trafficFlow << " veh/min\n";
}

void TransportSystem::deactivate() {
    isOperational = false;
    trafficFlow = 0;
    healthStatus = 0.0;
    std::cout << "[TRANSPORT] System deactivated\n";
}

std::string TransportSystem::getStatus() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "[TRANSPORT SYSTEM] Health: " << healthStatus << "% | "
        << "Flow: " << trafficFlow << "/" << maxCapacity << " veh/min | "
        << "Speed: " << averageSpeed << " KPH | "
        << "Active Vehicles: " << activeVehicles << " | "
        << (accidentResponse ? "ACCIDENT RESPONSE ACTIVE" : "Normal");
    return oss.str();
}

void TransportSystem::manageTraffic(int flowRate) {
    if (isOperational) {
        trafficFlow = std::min(flowRate, maxCapacity);
        if (trafficFlow > maxCapacity * 0.9) {
            averageSpeed *= 0.8;
            healthStatus -= 5.0;
        }
    }
}

void TransportSystem::respondToAccident(const Event& event) {
    std::cout << "[TRANSPORT ALERT] Accident response: " << event.description << "\n";
    accidentResponse = true;
    trafficFlow *= 0.6;
    averageSpeed *= 0.5;
    activeVehicles = std::min(activeVehicles + 10, 60);
    healthStatus -= 10.0;
    if (healthStatus < 0.0) healthStatus = 0.0;
}

void TransportSystem::optimizeRoutes() {
    std::cout << "[TRANSPORT] Optimizing traffic routes...\n";
    trafficFlow = trafficFlow * 1.15;
    if (trafficFlow > maxCapacity) trafficFlow = maxCapacity;
    averageSpeed = 65.0;
    healthStatus = std::min(100.0, healthStatus + 5.0);
}

// ──────────────────────────────────────────────────────────────────────────────
// HealthSystem Implementation
// ──────────────────────────────────────────────────────────────────────────────

void HealthSystem::processEvent(const Event& event) {
    if (event.type == EventType::PopulationCrisis) {
        respondToHealthCrisis(event);
    } else if (event.priority == EventPriority::Critical) {
        activateCrisisProtocol();
    }
}

void HealthSystem::activate() {
    isOperational = true;
    occupiedBeds = hospitalBedCount / 2;
    healthStatus = 100.0;
    std::cout << "[HEALTH] System activated - capacity: " << hospitalBedCount << " beds\n";
}

void HealthSystem::deactivate() {
    isOperational = false;
    occupiedBeds = 0;
    healthStatus = 0.0;
    std::cout << "[HEALTH] System deactivated\n";
}

std::string HealthSystem::getStatus() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    double occupancyRate = static_cast<double>(occupiedBeds) / hospitalBedCount * 100.0;
    oss << "[HEALTH SYSTEM] Health: " << healthStatus << "% | "
        << "Occupancy: " << occupiedBeds << "/" << hospitalBedCount << " ("
        << occupancyRate << "%) | "
        << "Response Time: " << responseTime << " min | "
        << "Ambulances: " << ambulancesActive << " | "
        << (crisisMode ? "CRISIS MODE ACTIVE" : "Normal");
    return oss.str();
}

void HealthSystem::provideCare(int patients) {
    if (isOperational) {
        int availableBeds = hospitalBedCount - occupiedBeds;
        int admittedPatients = std::min(patients, availableBeds);
        occupiedBeds += admittedPatients;
        if (occupiedBeds > hospitalBedCount * 0.9) {
            responseTime += 2.0;
            healthStatus -= 3.0;
        }
    }
}

void HealthSystem::respondToHealthCrisis(const Event& event) {
    std::cout << "[HEALTH ALERT] Crisis response: " << event.description << "\n";
    crisisMode = true;
    occupiedBeds = std::min(occupiedBeds + 250, hospitalBedCount);
    ambulancesActive = std::min(ambulancesActive + 15, 60);
    responseTime *= 0.8;
    healthStatus -= 20.0;
    if (healthStatus < 0.0) healthStatus = 0.0;
}

void HealthSystem::activateCrisisProtocol() {
    std::cout << "[HEALTH] Crisis protocol activated\n";
    crisisMode = true;
    ambulancesActive = 60;
    responseTime = 5.0;
    healthStatus = 85.0;
}

// ──────────────────────────────────────────────────────────────────────────────
// SecuritySystem Implementation
// ──────────────────────────────────────────────────────────────────────────────

void SecuritySystem::processEvent(const Event& event) {
    if (event.type == EventType::SecurityThreat) {
        respondToThreat(event);
    } else if (event.priority == EventPriority::Critical) {
        activateLockdown();
    }
}

void SecuritySystem::activate() {
    isOperational = true;
    surveilanceActive = true;
    healthStatus = 100.0;
    std::cout << "[SECURITY] System activated - units: " << policeUnitsActive << "\n";
}

void SecuritySystem::deactivate() {
    isOperational = false;
    lockdownActive = false;
    healthStatus = 0.0;
    std::cout << "[SECURITY] System deactivated\n";
}

std::string SecuritySystem::getStatus() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << "[SECURITY SYSTEM] Health: " << healthStatus << "% | "
        << "Threat Level: " << threatLevel << "/10 | "
        << "Police Units: " << policeUnitsActive << " | "
        << "Surveillance: " << (surveilanceActive ? "ACTIVE" : "INACTIVE") << " | "
        << "Cybersecurity: Level " << cybersecurityLevel << " | "
        << (lockdownActive ? "LOCKDOWN ACTIVE" : "Normal");
    return oss.str();
}

void SecuritySystem::monitorCity(int incidents) {
    if (isOperational && surveilanceActive) {
        threatLevel = std::min(10, incidents / 10);
        if (threatLevel > 5) {
            policeUnitsActive = std::min(policeUnitsActive + 30, 200);
            healthStatus -= 5.0;
        }
    }
}

void SecuritySystem::respondToThreat(const Event& event) {
    std::cout << "[SECURITY ALERT] Threat response: " << event.description << "\n";
    threatLevel = std::min(10, threatLevel + 2);
    policeUnitsActive = std::min(policeUnitsActive + 20, 200);
    cybersecurityLevel = std::max(cybersecurityLevel - 1, 1);
    healthStatus -= 8.0;
    if (healthStatus < 0.0) healthStatus = 0.0;
}

void SecuritySystem::activateLockdown() {
    std::cout << "[SECURITY] CITYWIDE LOCKDOWN ACTIVATED\n";
    lockdownActive = true;
    policeUnitsActive = 150;
    surveilanceActive = true;
    cybersecurityLevel = 10;
    threatLevel = 8;
    healthStatus = 65.0;
}

#include <sstream>
