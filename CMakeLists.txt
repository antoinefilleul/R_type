cmake_minimum_required(VERSION 3.10)

# Set the project name
project(R_type)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Collect all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(R_type ${SOURCES})

# Link SFML libraries
target_link_libraries(R_type sfml-graphics sfml-window sfml-system)