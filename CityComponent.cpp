#include "CityComponent.h"
#include <iostream>
#include <iomanip>

// ──────────────────────────────────────────────────────────────────────────────
// NeoVerse AI City Survival System - CityComponent Implementation
// Author: Craig GAZIMBI (Student ID: 402417962)
// ──────────────────────────────────────────────────────────────────────────────

void CityComponent::displayComponentInfo() const {
    std::cout << "[" << componentName << " (ID: " << componentID << ")] "
              << "Health: " << std::fixed << std::setprecision(1)
              << healthStatus << "% | "
              << (isOperational ? "Operational" : "Offline") << "\n";
}
