# NeoVerse Quick Compilation Guide

**Author:** Craig GAZIMBI (402417962)

**Repository:** https://github.com/therealcraiggazimbi/neoverse-

---

## Get the Code (Step 1)

**Option A: Clone from GitHub (Recommended)**

```bash
git clone https://github.com/therealcraiggazimbi/neoverse-
cd neoverse-
```

**Option B: Download ZIP**

Visit: https://github.com/therealcraiggazimbi/neoverse-

Click "Code" → "Download ZIP" → Extract

---

## Fastest Way to Compile (Step 2)

### Using CLion (Recommended)

1. Open the project folder in CLion
2. Click "Build" button or press `Shift+F10`
3. Click "Run" or press `Shift+F10`

**Result:** Automatic compilation with debug symbols and optimizations.

---

## Command Line Compilation

### macOS/Linux (Clang++)

**Main Application:**

```bash
cd /Users/craiggazimbi/CLionProjects/untitled

clang++ -std=c++17 -Wall -Wextra -O2 \
    Main.cpp SimulationEngine.cpp Types.cpp \
    CityComponent.cpp Subsystems.cpp \
    -o neoverse_main

./neoverse_main
```

**Unit Tests:**

```bash
clang++ -std=c++17 -Wall -Wextra -O2 \
    UnitTests.cpp SimulationEngine.cpp Types.cpp \
    CityComponent.cpp Subsystems.cpp \
    -o neoverse_tests

./neoverse_tests
```

### macOS/Linux (GCC)

```bash
g++ -std=c++17 -Wall -Wextra -O2 \
    Main.cpp SimulationEngine.cpp Types.cpp \
    CityComponent.cpp Subsystems.cpp \
    -o neoverse_main

./neoverse_main
```

### Windows (MSVC)

```cmd
cd C:\path\to\project

cl /std:c++17 /EHsc /O2 Main.cpp SimulationEngine.cpp ^
    Types.cpp CityComponent.cpp Subsystems.cpp /Fe:neoverse_main.exe

neoverse_main.exe
```

### Windows (MinGW)

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o neoverse_main.exe ^
    Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp

neoverse_main.exe
```

---

## Test Execution

```bash
./neoverse_tests
```

**Expected Output:**

```
[PASS] Alice Chen should authenticate with correct password
[PASS] Queue should contain 3 events
[PASS] First dequeued event should be event 1 (FIFO)
...
Total Tests Run:      42
Tests Passed:        42 (100.0%)
```

---

## File Checklist Before Compilation

Verify these files exist in the project directory:

- [ ] Types.h (9.0K)
- [ ] Types.cpp (8.1K)
- [ ] CityComponent.h (2.5K)
- [ ] CityComponent.cpp (963B)
- [ ] Subsystems.h (10K)
- [ ] Subsystems.cpp (10K)
- [ ] SimulationEngine.h (11K)
- [ ] SimulationEngine.cpp (24K)
- [ ] Main.cpp (15K)
- [ ] UnitTests.cpp (24K)

**Total:** 2527 lines of C++17 code across 10 files

---

## Common Issues

**Issue: "undefined reference to"**
- Ensure ALL .cpp files are listed in compilation command
- Check for typos in filenames

**Issue: "cannot find header"**
- Verify #include paths are correct
- Ensure header files in same directory

**Issue: Compilation takes long time**
- Add `-O1` or `-O2` flag for optimizations
- Remove debug info with `-g0` if not needed

---

## Compilation Flags Explained

| Flag | Purpose |
|------|---------|
| `-std=c++17` | Use C++17 standard |
| `-Wall` | Enable all common warnings |
| `-Wextra` | Enable extra warnings |
| `-O2` | Optimize for performance |
| `-g` | Include debug symbols |
| `-o filename` | Output executable name |

---

## Running the Application

**Main Console Application:**

```bash
./neoverse_main
```

Navigate menus:
1. Authentication & Access Control
2. Simulation & Event Processing
3. Analytics & Performance Report
4. Exit System

**Test Suite:**

```bash
./neoverse_tests
```

Runs 42 unit tests across 7 test suites.

---

## CMake Build (Optional)

Create `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(NeoVerse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(neoverse_main
    Main.cpp
    SimulationEngine.cpp
    Types.cpp
    CityComponent.cpp
    Subsystems.cpp
)

add_executable(neoverse_tests
    UnitTests.cpp
    SimulationEngine.cpp
    Types.cpp
    CityComponent.cpp
    Subsystems.cpp
)

target_compile_options(neoverse_main PRIVATE -Wall -Wextra -O2)
target_compile_options(neoverse_tests PRIVATE -Wall -Wextra -O2)
```

Build:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

---

**End of Guide**

For detailed documentation, see README.md
