cmake_minimum_required(VERSION 3.11)
project(sRenderer)

# Set C++11 standard and strict compliance
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags (-Wall for warnings, -g for debug)
add_compile_options(-Wall -g)

# Include headers from "inc" directory
include_directories(inc)

# Automatically collect all .cpp files in src/
file(GLOB SOURCES "src/*.cpp")

# Copy entire directories to build folder
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/texture/ 
     DESTINATION ${CMAKE_BINARY_DIR}/texture)
     
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/obj/ 
     DESTINATION ${CMAKE_BINARY_DIR}/obj)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# (Optional) Set output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
