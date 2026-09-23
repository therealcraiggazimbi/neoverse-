#pragma once

#include "CityComponent.h"

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - Subsystem Implementations
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────────────────────
// PowerSystem: Manages electrical grid distribution and generation
// Handles power failures, load balancing, and emergency shutdowns
// ──────────────────────────────────────────────────────────────────────────────
class PowerSystem : public CityComponent {
private:
    double          powerLevel;         // Megawatts currently supplied
    double          maxCapacity;        // Maximum MW available
    double          currentDemand;      // MW currently demanded
    int             substationsActive;  // Number of active substations
    bool            emergencyMode;

public:
    PowerSystem() : CityComponent(1, "Power System"),
                    powerLevel(500.0), maxCapacity(800.0),
                    currentDemand(400.0), substationsActive(8),
                    emergencyMode(false) {}

    explicit PowerSystem(int id) : CityComponent(id, "Power System"),
                                   powerLevel(500.0), maxCapacity(800.0),
                                   currentDemand(400.0), substationsActive(8),
                                   emergencyMode(false) {}

    virtual ~PowerSystem() = default;

    // Implement pure virtual methods
    void processEvent(const Event& event) override;
    void activate() override;
    void deactivate() override;
    std::string getStatus() const override;

    // PowerSystem-specific methods
    void supplyPower(double megawatts);
    void respondToFailure(const Event& event);
    void activateEmergencyPower();

    // Accessors
    double getPowerLevel()      const { return powerLevel; }
    double getMaxCapacity()     const { return maxCapacity; }
    double getCurrentDemand()   const { return currentDemand; }
    int    getSubstationsActive() const { return substationsActive; }
    bool   isEmergencyMode()    const { return emergencyMode; }

    // Setters
    void setPowerLevel(double level)   { powerLevel = level; }
    void setCurrentDemand(double demand) { currentDemand = demand; }
    void setSubstationsActive(int count) { substationsActive = count; }
};

// ──────────────────────────────────────────────────────────────────────────────
// TransportSystem: Manages traffic flow, public transit, and emergency routing
// Handles congestion, accidents, and network overloads
// ──────────────────────────────────────────────────────────────────────────────
class TransportSystem : public CityComponent {
private:
    int             trafficFlow;        // Vehicles per minute through major routes
    int             maxCapacity;        // Maximum vehicles that can be handled
    int             activeVehicles;     // Public transport buses and trains
    double          averageSpeed;       // KPH on main routes
    bool            accidentResponse;

public:
    TransportSystem() : CityComponent(2, "Transport System"),
                        trafficFlow(350), maxCapacity(500),
                        activeVehicles(45), averageSpeed(60.0),
                        accidentResponse(false) {}

    explicit TransportSystem(int id) : CityComponent(id, "Transport System"),
                                       trafficFlow(350), maxCapacity(500),
                                       activeVehicles(45), averageSpeed(60.0),
                                       accidentResponse(false) {}

    virtual ~TransportSystem() = default;

    // Implement pure virtual methods
    void processEvent(const Event& event) override;
    void activate() override;
    void deactivate() override;
    std::string getStatus() const override;

    // TransportSystem-specific methods
    void manageTraffic(int flowRate);
    void respondToAccident(const Event& event);
    void optimizeRoutes();

    // Accessors
    int    getTrafficFlow()     const { return trafficFlow; }
    int    getMaxCapacity()     const { return maxCapacity; }
    int    getActiveVehicles()  const { return activeVehicles; }
    double getAverageSpeed()    const { return averageSpeed; }
    bool   isAccidentResponse() const { return accidentResponse; }

    // Setters
    void setTrafficFlow(int flow)     { trafficFlow = flow; }
    void setActiveVehicles(int count) { activeVehicles = count; }
    void setAverageSpeed(double speed) { averageSpeed = speed; }
};

// ──────────────────────────────────────────────────────────────────────────────
// HealthSystem: Manages hospital capacity, emergency medical response
// Handles health crises, epidemics, and patient distribution
// ──────────────────────────────────────────────────────────────────────────────
class HealthSystem : public CityComponent {
private:
    int             hospitalBedCount;   // Total beds available
    int             occupiedBeds;       // Currently occupied
    int             ambulancesActive;   // Mobile response units
    double          responseTime;       // Minutes for ambulance dispatch
    bool            crisisMode;

public:
    HealthSystem() : CityComponent(3, "Health System"),
                     hospitalBedCount(1500), occupiedBeds(800),
                     ambulancesActive(35), responseTime(8.5),
                     crisisMode(false) {}

    explicit HealthSystem(int id) : CityComponent(id, "Health System"),
                                    hospitalBedCount(1500), occupiedBeds(800),
                                    ambulancesActive(35), responseTime(8.5),
                                    crisisMode(false) {}

    virtual ~HealthSystem() = default;

    // Implement pure virtual methods
    void processEvent(const Event& event) override;
    void activate() override;
    void deactivate() override;
    std::string getStatus() const override;

    // HealthSystem-specific methods
    void provideCare(int patients);
    void respondToHealthCrisis(const Event& event);
    void activateCrisisProtocol();

    // Accessors
    int    getHospitalBedCount()  const { return hospitalBedCount; }
    int    getOccupiedBeds()      const { return occupiedBeds; }
    int    getAmbulancesActive()  const { return ambulancesActive; }
    double getResponseTime()      const { return responseTime; }
    bool   isCrisisMode()         const { return crisisMode; }

    // Setters
    void setOccupiedBeds(int count) { occupiedBeds = count; }
    void setAmbulancesActive(int count) { ambulancesActive = count; }
    void setResponseTime(double time) { responseTime = time; }
};

// ──────────────────────────────────────────────────────────────────────────────
// SecuritySystem: Manages law enforcement, surveillance, threat monitoring
// Handles security incidents, cyber threats, and emergency lockdowns
// ──────────────────────────────────────────────────────────────────────────────
class SecuritySystem : public CityComponent {
private:
    int             policeUnitsActive;  // Patrol cars and response teams
    int             threatLevel;        // 0 to 10 scale
    bool            surveilanceActive;  // CCTV monitoring enabled
    int             cybersecurityLevel; // Firewall/IDS defense tier
    bool            lockdownActive;

public:
    SecuritySystem() : CityComponent(4, "Security System"),
                       policeUnitsActive(120), threatLevel(3),
                       surveilanceActive(true), cybersecurityLevel(7),
                       lockdownActive(false) {}

    explicit SecuritySystem(int id) : CityComponent(id, "Security System"),
                                      policeUnitsActive(120), threatLevel(3),
                                      surveilanceActive(true), cybersecurityLevel(7),
                                      lockdownActive(false) {}

    virtual ~SecuritySystem() = default;

    // Implement pure virtual methods
    void processEvent(const Event& event) override;
    void activate() override;
    void deactivate() override;
    std::string getStatus() const override;

    // SecuritySystem-specific methods
    void monitorCity(int incidents);
    void respondToThreat(const Event& event);
    void activateLockdown();

    // Accessors
    int  getPoliceUnitsActive()   const { return policeUnitsActive; }
    int  getThreatLevel()         const { return threatLevel; }
    bool isSurveillanceActive()   const { return surveilanceActive; }
    int  getCybersecurityLevel()  const { return cybersecurityLevel; }
    bool isLockdownActive()       const { return lockdownActive; }

    // Setters
    void setThreatLevel(int level)      { threatLevel = level; }
    void setPoliceUnitsActive(int count) { policeUnitsActive = count; }
    void setCybersecurityLevel(int level) { cybersecurityLevel = level; }
};
