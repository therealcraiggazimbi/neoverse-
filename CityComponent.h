#pragma once

#include "Types.h"

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - CityComponent Abstract Base Class
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────────────────────
// CityComponent: Abstract base class for all city subsystems
// Demonstrates polymorphism, virtual methods, and dynamic dispatch
// ──────────────────────────────────────────────────────────────────────────────
class CityComponent {
protected:
    int             componentID;
    std::string     componentName;
    double          healthStatus;       // 0.0 to 100.0 percentage
    bool            isOperational;

public:
    CityComponent() : componentID(0), healthStatus(100.0), isOperational(true) {}

    CityComponent(int id, const std::string& name)
        : componentID(id), componentName(name),
          healthStatus(100.0), isOperational(true) {}

    virtual ~CityComponent() = default;

    // Pure virtual methods - each subsystem implements its own logic
    virtual void processEvent(const Event& event) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual std::string getStatus() const = 0;

    // Concrete accessors
    int             getComponentID()      const { return componentID; }
    const std::string& getComponentName() const { return componentName; }
    double          getHealthStatus()     const { return healthStatus; }
    bool            getOperationalStatus() const { return isOperational; }

    // Concrete setters
    void setHealthStatus(double health) { healthStatus = health; }
    void setOperational(bool operational) { isOperational = operational; }

    // Concrete helper
    void displayComponentInfo() const;
};
