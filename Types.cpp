#include "Types.h"
#include <iostream>
#include <iomanip>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Type Implementations
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────────────────────
// Engineer Class Implementation
// ──────────────────────────────────────────────────────────────────────────────

Engineer::Engineer(const std::string& id, const std::string& user,
                   const std::string& password, ClearanceLevel level)
    : engineerID(id), username(user), clearanceLevel(level), isAuthenticated(false) {
    encryptedPassword = encryptPassword(password);
}

bool Engineer::authenticate(const std::string& providedPassword) {
    std::string encrypted = encryptPassword(providedPassword);
    if (encrypted == encryptedPassword) {
        isAuthenticated = true;
        return true;
    }
    return false;
}

std::string Engineer::encryptPassword(const std::string& plaintext) const {
    std::string encrypted = plaintext;
    for (size_t i = 0; i < encrypted.length(); ++i) {
        encrypted[i] = encrypted[i] ^ 0x5A;
    }
    return encrypted;
}

std::string Engineer::decryptPassword(const std::string& encrypted) const {
    return encryptPassword(encrypted);
}

std::string Engineer::getClearanceLevelString() const {
    switch (clearanceLevel) {
        case ClearanceLevel::Low:    return "Low";
        case ClearanceLevel::Medium: return "Medium";
        case ClearanceLevel::High:   return "High";
        default:                     return "Unknown";
    }
}

void Engineer::displayInfo() const {
    std::cout << std::left << std::setw(12) << engineerID
              << " | " << std::setw(15) << username
              << " | " << std::setw(8) << getClearanceLevelString()
              << " | " << (isAuthenticated ? "Authenticated" : "Not Authenticated") << "\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// SensorReading Display Implementation
// ──────────────────────────────────────────────────────────────────────────────

void SensorReading::display() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "[" << timestamp << "] "
              << "Energy: " << energyUsage << " MW | "
              << "Traffic: " << trafficDensity << "% | "
              << "Population: " << populationCount << " | "
              << "Network: " << networkLoad << "% | "
              << "Health Alerts: " << healthAlerts << " | "
              << "Security: " << securityIncidents << "\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// CityLog Display Implementation
// ──────────────────────────────────────────────────────────────────────────────

std::string CityLog::getEventTypeString() const {
    switch (eventType) {
        case EventType::TrafficAccident:   return "TrafficAccident";
        case EventType::PowerFailure:      return "PowerFailure";
        case EventType::NetworkOverload:   return "NetworkOverload";
        case EventType::WeatherAlert:      return "WeatherAlert";
        case EventType::PopulationCrisis:  return "PopulationCrisis";
        case EventType::SecurityThreat:    return "SecurityThreat";
        default:                           return "Unknown";
    }
}

std::string CityLog::getPriorityString() const {
    switch (priority) {
        case EventPriority::Low:      return "Low";
        case EventPriority::Medium:   return "Medium";
        case EventPriority::High:     return "High";
        case EventPriority::Critical: return "Critical";
        default:                      return "Unknown";
    }
}

void CityLog::display() const {
    std::cout << "[" << timestamp << "] "
              << std::setw(20) << std::left << getEventTypeString()
              << " | Priority: " << std::setw(8) << getPriorityString()
              << " | " << description
              << " (System: " << systemAffected << ")\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// Event Display Implementation
// ──────────────────────────────────────────────────────────────────────────────

void Event::display() const {
    std::cout << "Event #" << eventID
              << " | Type: " << static_cast<int>(type)
              << " | Priority: " << static_cast<int>(priority)
              << " | Latency: " << std::fixed << std::setprecision(2)
              << responseLatency << " ms | " << description << "\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// EmergencyEvent Display Implementation
// ──────────────────────────────────────────────────────────────────────────────

void EmergencyEvent::display() const {
    std::cout << "EMERGENCY #" << emergencyID
              << " | Type: " << static_cast<int>(type)
              << " | Priority Mask: " << systemsPriority
              << " | " << description
              << " [" << timestamp << "]\n";
}

// ──────────────────────────────────────────────────────────────────────────────
// PerformanceMetrics Display Implementation
// ──────────────────────────────────────────────────────────────────────────────

void PerformanceMetrics::display() const {
    std::cout << "\n=== Performance Metrics ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Response Latency: " << averageResponseLatency << " ms\n";
    std::cout << "Total Events Processed: " << totalEventsProcessed << "\n";
    std::cout << "Modal Event Type: " << modalEventType
              << " (Frequency: " << modalEventCount << ")\n";
    std::cout << "\n=== Subsystem Health ===\n";
    std::cout << "Power System Health: " << powerSystemHealth << "%\n";
    std::cout << "Transport System Health: " << transportSystemHealth << "%\n";
    std::cout << "Health System Health: " << healthSystemHealth << "%\n";
    std::cout << "Security System Health: " << securitySystemHealth << "%\n";
}
