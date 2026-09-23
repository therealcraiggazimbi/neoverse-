@echo off
REM ──────────────────────────────────────────────────────────────────────────────
REM NeoVerse AI City Survival System - Windows Build and Run Script
REM Author: Craig GAZIMBI (Student ID: 402417962)
REM Purpose: Automated compilation and execution for Windows (MSVC/MinGW)
REM ──────────────────────────────────────────────────────────────────────────────

setlocal enabledelayedexpansion

set EXECUTABLE_NAME=neoverse_main.exe
set TEST_EXECUTABLE=neoverse_tests.exe
set CXX_STANDARD=/std:c++17
set COMPILER_FLAGS=/EHsc /O2 /W3

echo.
echo ====================================================================
echo     NeoVerse AI City Survival System - Windows Build Tool
echo              Craig GAZIMBI - Student 402417962
echo ====================================================================
echo.

REM Check if MSVC cl.exe is available
where cl.exe >nul 2>nul
if %errorlevel% equ 0 (
    set COMPILER=cl.exe
    set COMPILER_TYPE=MSVC
    echo Using compiler: MSVC (cl.exe)
) else (
    REM Try MinGW g++
    where g++.exe >nul 2>nul
    if %errorlevel% equ 0 (
        set COMPILER=g++.exe
        set COMPILER_TYPE=MinGW
        echo Using compiler: MinGW (g++.exe)
    ) else (
        echo ERROR: Neither MSVC (cl.exe) nor MinGW (g++.exe) found.
        echo Please install Visual Studio or MinGW.
        exit /b 1
    )
)

echo C++ Standard: C++17
echo.

REM Check if source files exist
set "missing=0"
for %%f in (Main.cpp SimulationEngine.cpp SimulationEngine.h Types.cpp Types.h CityComponent.cpp CityComponent.h Subsystems.cpp Subsystems.h) do (
    if not exist "%%f" (
        echo ERROR: Required file not found: %%f
        set missing=1
    )
)

if %missing% equ 1 (
    exit /b 1
)

echo ^[OK] All source files found
echo.

REM Display menu
echo Choose an option:
echo   1) Compile and run main application
echo   2) Compile and run unit tests
echo   3) Compile both ^(no run^)
echo   4) Clean ^(remove executables^)
echo   5) Exit
echo.

set /p choice="Enter selection (1-5): "

if "%choice%"=="1" (
    echo.
    echo [Step 1/3] Compiling main application...
    if "%COMPILER_TYPE%"=="MSVC" (
        echo Command: %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%EXECUTABLE_NAME%
        echo.
        %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%EXECUTABLE_NAME%
    ) else (
        echo Command: %COMPILER% -std=c++17 -Wall -O2 Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %EXECUTABLE_NAME%
        echo.
        %COMPILER% -std=c++17 -Wall -O2 Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %EXECUTABLE_NAME%
    )

    if %errorlevel% equ 0 (
        echo [OK] Compilation successful
        echo.
        echo [Step 2/3] Executable is ready
        echo.
        echo [Step 3/3] Running application...
        echo.
        %EXECUTABLE_NAME%
    ) else (
        echo [ERROR] Compilation failed
        exit /b 1
    )

) else if "%choice%"=="2" (
    echo.
    echo [Step 1/3] Compiling unit tests...
    if "%COMPILER_TYPE%"=="MSVC" (
        echo Command: %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%TEST_EXECUTABLE%
        echo.
        %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%TEST_EXECUTABLE%
    ) else (
        echo Command: %COMPILER% -std=c++17 -Wall -O2 UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %TEST_EXECUTABLE%
        echo.
        %COMPILER% -std=c++17 -Wall -O2 UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %TEST_EXECUTABLE%
    )

    if %errorlevel% equ 0 (
        echo [OK] Compilation successful
        echo.
        echo [Step 2/3] Test executable is ready
        echo.
        echo [Step 3/3] Running tests...
        echo.
        %TEST_EXECUTABLE%
    ) else (
        echo [ERROR] Compilation failed
        exit /b 1
    )

) else if "%choice%"=="3" (
    echo.
    echo Compiling main application...
    if "%COMPILER_TYPE%"=="MSVC" (
        %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%EXECUTABLE_NAME%
    ) else (
        %COMPILER% -std=c++17 -Wall -O2 Main.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %EXECUTABLE_NAME%
    )

    if %errorlevel% equ 0 (
        echo [OK] Main application compiled
    ) else (
        echo [ERROR] Main compilation failed
        exit /b 1
    )

    echo.
    echo Compiling unit tests...
    if "%COMPILER_TYPE%"=="MSVC" (
        %COMPILER% %CXX_STANDARD% %COMPILER_FLAGS% UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp /Fe:%TEST_EXECUTABLE%
    ) else (
        %COMPILER% -std=c++17 -Wall -O2 UnitTests.cpp SimulationEngine.cpp Types.cpp CityComponent.cpp Subsystems.cpp -o %TEST_EXECUTABLE%
    )

    if %errorlevel% equ 0 (
        echo [OK] Unit tests compiled
    ) else (
        echo [ERROR] Test compilation failed
        exit /b 1
    )

    echo.
    echo [OK] Both executables ready:
    echo    - %EXECUTABLE_NAME% (main application)
    echo    - %TEST_EXECUTABLE% (unit tests)

) else if "%choice%"=="4" (
    echo.
    if exist "%EXECUTABLE_NAME%" (
        del %EXECUTABLE_NAME%
        echo [OK] Removed %EXECUTABLE_NAME%
    )
    if exist "%TEST_EXECUTABLE%" (
        del %TEST_EXECUTABLE%
        echo [OK] Removed %TEST_EXECUTABLE%
    )

    REM Clean up generated data files
    for %%f in (neoverse_*.csv) do del %%f 2>nul
    echo [OK] Cleaned up

) else if "%choice%"=="5" (
    echo Exiting...
    exit /b 0

) else (
    echo [ERROR] Invalid selection. Exiting.
    exit /b 1
)

echo.
echo [OK] Operation completed successfully
echo.
pause
