cmake_minimum_required(VERSION 3.10)
project(SensorProject C CXX)

# Set C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)  # Updated to C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Make sure C++14 is required

# Add the main source file
add_executable(sensor_app cmain.cpp)

# Enable testing
enable_testing()

# Add the test directory
add_subdirectory(test)
