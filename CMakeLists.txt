# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(limits_of_detection)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Find Boost libraries
find_package(Boost REQUIRED)


## Declare the C++ library
add_library(${PROJECT_NAME} SHARED 
src/limits_of_detection.cpp
)

# Link Boost libraries (e.g., math)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Add the executable
add_executable(limits_of_detection_example 
    src/example_1.cpp
)

# Link Boost libraries (e.g., math)
target_link_libraries(limits_of_detection_example ${PROJECT_NAME})

#############
## Install ##
#############

## Mark header files for installation
install(
  DIRECTORY include/${PROJECT_NAME}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include
  FILES_MATCHING
  PATTERN "*.hpp" 
)

## Mark libraries for installation
install(TARGETS  
  ${PROJECT_NAME}
  EXPORT   "${PROJECT_NAME}Targets"
  LIBRARY  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}
  INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

## Install the targets file associated with the lib
install(EXPORT 
  "${PROJECT_NAME}Targets"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}/cmake/
)

## Configure the config file to have the necessary defines
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  @ONLY
)

## Finally install the config file so that cmake can find it
install(FILES
  "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/${PROJECT_NAME}/cmake
)