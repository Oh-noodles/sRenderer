cmake_minimum_required(VERSION 3.11)
project(sRenderer)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set C++11 standard and strict compliance
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags (-Wall for warnings, -g for debug)
add_compile_options(-Wall -g)

# Include headers from "inc" directory
include_directories(inc)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)


# Automatically collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Copy entire directories to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/texture/ 
     DESTINATION ${CMAKE_BINARY_DIR}/texture)
     
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/obj/ 
     DESTINATION ${CMAKE_BINARY_DIR}/obj)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)

# (Optional) Set output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
