cmake_minimum_required(VERSION 3.10)

# Define the project name
project(VolatilityTrading CXX)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Prefer standard-compliant features

# Define the include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/data
    ${CMAKE_SOURCE_DIR}/include/models
    ${CMAKE_SOURCE_DIR}/include/strategy
    ${CMAKE_SOURCE_DIR}/include/utils
)

# Add source files
set(SOURCE_FILES
    src/main.cpp
    src/utils/math_utils.cpp
    src/utils/date_utils.cpp # Add the new date utility source file
    src/models/black_scholes.cpp
    src/models/volatility_forecast.cpp
    src/models/risk_management.cpp
    src/strategy/implied_vol_strategy.cpp
    src/data/data_loader.cpp
)

# Add the executable target
add_executable(VolatilityTrading ${SOURCE_FILES})
