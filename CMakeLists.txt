# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(LimitsOfDetection)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Find Boost libraries
find_package(Boost REQUIRED)

# Add the executable
add_executable(limits_of_detection 
    src/limits_of_detection.cpp 
    src/example_1.cpp
)

# Link Boost libraries (e.g., math)
target_link_libraries(limits_of_detection ${Boost_LIBRARIES})
