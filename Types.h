#pragma once

#include <string>
#include <vector>
#include <chrono>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Type Definitions
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

enum class ClearanceLevel { Low = 0, Medium = 1, High = 2 };

enum class EventType {
    TrafficAccident = 0,
    PowerFailure = 1,
    NetworkOverload = 2,
    WeatherAlert = 3,
    PopulationCrisis = 4,
    SecurityThreat = 5
};

enum class EventPriority {
    Low = 0,
    Medium = 1,
    High = 2,
    Critical = 3
};

// ──────────────────────────────────────────────────────────────────────────────
// Engineer class: AI Agent for city system access with authentication
// Attributes: ID, username, encrypted password, clearance level
// ──────────────────────────────────────────────────────────────────────────────
class Engineer {
private:
    std::string         engineerID;         // ENG001, ENG002, etc.
    std::string         username;
    std::string         encryptedPassword;  // Simple XOR encryption for demonstration
    ClearanceLevel      clearanceLevel;
    bool                isAuthenticated;

public:
    Engineer() : clearanceLevel(ClearanceLevel::Low), isAuthenticated(false) {}

    Engineer(const std::string& id, const std::string& user,
             const std::string& password, ClearanceLevel level);

    virtual ~Engineer() = default;

    // Authentication and access control
    bool authenticate(const std::string& providedPassword);

    // Accessors
    const std::string&  getEngineerID()         const { return engineerID; }
    const std::string&  getUsername()           const { return username; }
    ClearanceLevel      getClearanceLevel()     const { return clearanceLevel; }
    bool                getAuthenticationStatus() const { return isAuthenticated; }

    // Setters
    void setAuthenticated(bool auth) { isAuthenticated = auth; }

    // Utility
    std::string getClearanceLevelString() const;
    void displayInfo() const;

private:
    std::string encryptPassword(const std::string& plaintext) const;
    std::string decryptPassword(const std::string& encrypted) const;
};

// ──────────────────────────────────────────────────────────────────────────────
// SensorReading: Daily city metrics snapshot
// ──────────────────────────────────────────────────────────────────────────────
struct SensorReading {
    std::string         timestamp;
    double              energyUsage;       // Megawatts
    double              trafficDensity;    // Percentage
    int                 populationCount;   // NPC citizens
    double              networkLoad;       // Percentage
    int                 healthAlerts;      // Hospital admissions
    int                 securityIncidents; // Police calls

    SensorReading() : energyUsage(0.0), trafficDensity(0.0),
                      populationCount(0), networkLoad(0.0),
                      healthAlerts(0), securityIncidents(0) {}

    SensorReading(const std::string& ts, double energy, double traffic,
                  int population, double network, int health, int security)
        : timestamp(ts), energyUsage(energy), trafficDensity(traffic),
          populationCount(population), networkLoad(network),
          healthAlerts(health), securityIncidents(security) {}

    void display() const;
};

// ──────────────────────────────────────────────────────────────────────────────
// CityLog: Historical event record for linked list storage
// ──────────────────────────────────────────────────────────────────────────────
struct CityLog {
    std::string     timestamp;
    EventType       eventType;
    EventPriority   priority;
    std::string     description;
    std::string     systemAffected;

    CityLog() : eventType(EventType::TrafficAccident), priority(EventPriority::Low) {}

    CityLog(const std::string& ts, EventType type, EventPriority pri,
            const std::string& desc, const std::string& system)
        : timestamp(ts), eventType(type), priority(pri),
          description(desc), systemAffected(system) {}

    std::string getEventTypeString() const;
    std::string getPriorityString() const;
    void display() const;
};

// ──────────────────────────────────────────────────────────────────────────────
// Event: Standard FIFO event structure for queue processing
// ──────────────────────────────────────────────────────────────────────────────
struct Event {
    int             eventID;
    EventType       type;
    EventPriority   priority;
    std::string     description;
    std::string     timestamp;
    double          responseLatency;    // Milliseconds for performance tracking

    Event() : eventID(0), type(EventType::TrafficAccident),
              priority(EventPriority::Low), responseLatency(0.0) {}

    Event(int id, EventType t, EventPriority p, const std::string& desc,
          const std::string& ts)
        : eventID(id), type(t), priority(p), description(desc),
          timestamp(ts), responseLatency(0.0) {}

    void display() const;
};

// ──────────────────────────────────────────────────────────────────────────────
// EmergencyEvent: LIFO priority override for critical situations
// ──────────────────────────────────────────────────────────────────────────────
struct EmergencyEvent {
    int             emergencyID;
    EventType       type;
    std::string     description;
    std::string     timestamp;
    int             systemsPriority;    // Which systems must override (bitmask)

    EmergencyEvent() : emergencyID(0), type(EventType::SecurityThreat),
                       systemsPriority(0) {}

    EmergencyEvent(int id, EventType t, const std::string& desc,
                   const std::string& ts, int priority)
        : emergencyID(id), type(t), description(desc),
          timestamp(ts), systemsPriority(priority) {}

    void display() const;
};

// ──────────────────────────────────────────────────────────────────────────────
// Performance metrics for analytics
// ──────────────────────────────────────────────────────────────────────────────
struct PerformanceMetrics {
    double              averageResponseLatency;
    int                 totalEventsProcessed;
    int                 modalEventType;         // Most frequent event type
    int                 modalEventCount;
    double              powerSystemHealth;
    double              transportSystemHealth;
    double              healthSystemHealth;
    double              securitySystemHealth;

    PerformanceMetrics() : averageResponseLatency(0.0),
                          totalEventsProcessed(0), modalEventType(0),
                          modalEventCount(0), powerSystemHealth(100.0),
                          transportSystemHealth(100.0),
                          healthSystemHealth(100.0),
                          securitySystemHealth(100.0) {}

    void display() const;
};
