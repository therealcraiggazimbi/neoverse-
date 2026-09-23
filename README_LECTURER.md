# NeoVerse – AI City Survival System

> **Programming 622 Assignment**  
> **Developer:** Craig Gazimbi  
> **Institution:** Richfield Graduate Institute of Technology  
> **Year:** 2026

---

## Clone Repository (Recommended)

Get all source code and documentation from GitHub:

```bash
git clone https://github.com/therealcraiggazimbi/neoverse-
cd neoverse-
bash NeoVerse              # Automated compilation and execution
```

Or download the ZIP file from: https://github.com/therealcraiggazimbi/neoverse-/archive/main.zip

---

## How to Compile

Requires `g++` or `clang++` with C++17 support (GCC 7+ or Clang 5+).

```bash
g++ -std=c++17 *.cpp -o neoverse_main
```

Or on macOS/Linux with clang:

```bash
clang++ -std=c++17 -Wall -O2 *.cpp -o neoverse_main
```

---

## How to Run

```bash
./neoverse_main        # Linux / macOS
neoverse_main.exe      # Windows (compiled with MSVC)
```

> CSV data files are created automatically on first run in the current working directory.

---

## Running Unit Tests

Compile tests:

```bash
g++ -std=c++17 UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o neoverse_tests
```

Run tests:

```bash
./neoverse_tests
```

**Expected Output:** 42/42 tests passing (100%)

---

## Default Engineer Login Credentials

| Engineer ID | Username    | Password          | Clearance |
|-------------|-------------|-------------------|-----------|
| ENG001      | alice_chen  | secure_pass_123   | High      |
| ENG002      | bob_smith   | password_456      | Medium    |
| ENG003      | carol_jones | pass_789          | Low       |

> Passwords are encrypted using XOR cipher (educational implementation).

---

## Main Menu Operations

From the main menu, users can select:

| Option | Function |
|--------|----------|
| 1 | Authentication & Access Control (Login, Register, Logout) |
| 2 | Simulation & Event Processing (Run simulation, add events) |
| 3 | Analytics & Performance Report (View metrics, export data) |
| 4 | Exit System |

---

## Authentication Workflow

1. Select option **1** from main menu
2. Choose **1 – Login Engineer**
3. Enter username: `alice_chen`
4. Enter password: `secure_pass_123`
5. You are now authenticated at **High** clearance level

After login, you can access simulation and analytics menus.

---

## Simulation Workflow

1. Log in as an engineer
2. Select option **2 – Simulation & Event Processing**
3. Choose from:
   - **1** – Run full simulation (50 automated events)
   - **2** – Add manual event (custom event type, priority, description)
   - **3** – Add sensor reading (energy, traffic, population, etc.)
   - **4** – Display subsystem status (Power, Transport, Health, Security)
   - **5** – Process next event from queue
   - **6** – View simulation status (queue/stack size, event count)
   - **7** – Reset simulation (clear all data)

---

## Analytics & Export

1. Log in as an engineer
2. Select option **3 – Analytics & Performance Report**
3. Options:
   - **1** – Display performance report (latency, events processed, subsystem health)
   - **2** – View recent sensor data (last 5, 10, 20 readings)
   - **3** – View historical logs (events, timestamps, descriptions)
   - **4** – Sort sensor readings by energy usage (std::sort O(n log n))
   - **5** – Find peak traffic density (std::max_element O(n))
   - **6** – Find lowest energy usage (std::min_element O(n))
   - **7** – Count critical events (std::count_if O(n))
   - **8** – Export data to CSV

**Export Output Files:**
- `neoverse_sensors.csv` – Sensor readings with timestamps
- `neoverse_logs.csv` – Historical events and descriptions
- `neoverse_metrics.csv` – Performance metrics snapshot

---

## Data Files

| File | Description |
|------|-------------|
| `engineers.dat` | Binary: engineer credentials (encrypted passwords) |
| `events.dat` | CSV export of processed events |
| `city_logs.dat` | Text: historical event log |
| `config.txt` | System configuration and statistics |
| `neoverse_sensors.csv` | CSV export of sensor readings |
| `neoverse_logs.csv` | CSV export of city logs |
| `neoverse_metrics.csv` | CSV export of performance metrics |

> CSV files are human-readable and compatible with Excel, Google Sheets, Tableau.

---

## City Subsystems

The simulation manages 4 interdependent subsystems:

### PowerSystem
- Electrical grid capacity: 0-800 MW
- Responds to power failure events
- Emergency backup activation
- Health status tracking (0-100%)

### TransportSystem
- Traffic flow: 0-500 vehicles/minute
- Route optimization algorithms
- Accident response protocols
- Speed monitoring (KPH)

### HealthSystem
- Hospital beds: 1500 total capacity
- Ambulance units: up to 60 active
- Response time: 5-8 minutes
- Crisis mode activation

### SecuritySystem
- Police units: up to 200 active
- Threat level: 0-10 scale
- Surveillance monitoring (CCTV)
- Cybersecurity defense (levels 1-10)
- Citywide lockdown capability

---

## Event Types and Priorities

**Event Types:**
- 0 – Traffic Accident
- 1 – Power Failure
- 2 – Network Overload
- 3 – Weather Alert
- 4 – Population Crisis
- 5 – Security Threat

**Event Priorities:**
- 0 – Low (minor incidents)
- 1 – Medium (moderate impact)
- 2 – High (significant disruption)
- 3 – Critical (system-wide threat)

**Queue vs Stack:**
- **FIFO Queue:** Regular events processed in arrival order (fairness)
- **LIFO Stack:** Emergency events override queue (preemption)

---

## Unit Tests

**Test Suites (42 total assertions):**

| Suite | Tests | Coverage |
|-------|-------|----------|
| Authentication Logic | 8 | Login, registration, clearance verification |
| FIFO vs LIFO | 8 | Queue ordering, stack ordering, preemption |
| Polymorphism | 7 | Virtual dispatch, subsystem activation |
| STL Algorithms | 7 | sort, max_element, min_element, count_if |
| File Persistence | 8 | Binary I/O, CSV export, round-trip validation |
| Data Management | 7 | Vector access, list operations, complexity |
| Binary Search | 4 | O(log n) vs O(n) comparison |

---

## Architecture Overview

```
CityComponent (abstract base)
├── PowerSystem
├── TransportSystem
├── HealthSystem
└── SecuritySystem

SimulationEngine (orchestrator)
├── std::vector<Engineer> – authentication
├── std::vector<SensorReading> – sensor data (O(1) access)
├── std::list<CityLog> – historical logs (unbounded)
├── std::queue<Event> – FIFO event processing
├── std::stack<EmergencyEvent> – LIFO emergency override
└── std::vector<shared_ptr<CityComponent>> – polymorphic subsystems

Types
├── Engineer – credentials, clearance
├── Event – ID, type, priority, latency
├── EmergencyEvent – critical override
├── SensorReading – energy, traffic, population, etc.
├── CityLog – historical record
└── PerformanceMetrics – analytics aggregation
```

---

## Key Features

- **Authentication:** Encrypted password storage, binary search O(log n)  
- **Data Structures:** Vector (O(1) access), List (O(1) insert), Queue (FIFO), Stack (LIFO)  
- **Polymorphism:** Virtual methods, dynamic dispatch, 4 subsystem implementations  
- **Algorithms:** std::sort (O(n log n)), max/min (O(n)), count_if (O(n))  
- **File I/O:** Binary serialization, CSV export  
- **Testing:** 42 unit tests  

---

## Big-O Complexity Summary

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Find engineer (linear) | O(n) | Worst case: check all engineers |
| Find engineer (binary) | O(log n) | 50x faster for 1M engineers |
| Add sensor reading | O(1) | Vector push_back (amortized) |
| Access sensor by index | O(1) | Direct memory access |
| Add city log | O(1) | List push_back |
| Sort readings | O(n log n) | std::sort with lambda comparator |
| Find max traffic | O(n) | std::max_element linear scan |
| Count critical events | O(n) | std::count_if predicate check |

---

## File Structure

```
/Users/craiggazimbi/CLionProjects/untitled/
├── README_LECTURER.md          ← This file
├── README.md                   ← Detailed technical guide
├── COMPILATION_GUIDE.md        ← Platform-specific compilation
├── DELIVERY_SUMMARY.md         ← Specification compliance matrix
├── Types.h / Types.cpp         ← Data types (Engineer, Event, etc.)
├── CityComponent.h / .cpp      ← Abstract base class
├── Subsystems.h / .cpp         ← PowerSystem, TransportSystem, etc.
├── SimulationEngine.h / .cpp   ← Main orchestrator (1200+ lines)
├── Main.cpp                    ← Interactive console application
├── UnitTests.cpp               ← 42 unit tests
└── NeoVerse                    ← Build/run script (optional)
```

---

## Quick Start for Lecturers

**1. Compile:**

```bash
cd /Users/craiggazimbi/CLionProjects/untitled
g++ -std=c++17 *.cpp -o neoverse_main
```

**2. Run:**

```bash
./neoverse_main
```

**3. Test Login (High Clearance):**

```
Menu: 1 (Authentication)
Menu: 1 (Login)
Username: alice_chen
Password: secure_pass_123
```

**4. Run Simulation:**

```
Menu: 2 (Simulation)
Menu: 1 (Run simulation - 50 events)
```

**5. View Results:**

```
Menu: 3 (Analytics)
Menu: 1 (Performance report)
Menu: 8 (Export to CSV)
```

**Files Generated:**
- `neoverse_sensors.csv`
- `neoverse_logs.csv`
- `neoverse_metrics.csv`

---



## Troubleshooting

**Compilation fails with "undefined reference":**
- Ensure ALL .cpp files are in compile command
- Check filenames for typos

**Test fails unexpectedly:**
- Verify test files are unmodified
- Run with `./neoverse_tests` (verbose output)

**CSV export empty:**
- Run simulation first (menu 2 → option 1)
- Then export (menu 3 → option 8)

**Cannot authenticate:**
- Default credentials: `alice_chen` / `secure_pass_123`
- Check password is exact match (case-sensitive)

---

## Contact & Support

For implementation details, see:
- `README.md` – Full technical documentation (28KB)
- `COMPILATION_GUIDE.md` – Platform-specific instructions
- `DELIVERY_SUMMARY.md` – Specification compliance checklist

---

**NeoVerse AI City Survival System**  
Craig Gazimbi | 402417962 | 2026-09-23
