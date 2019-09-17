cmake_minimum_required(VERSION 3.0)
project(sbgc)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find source files
file(GLOB SOURCES src/*.cpp)

# Add source files
add_library(${PROJECT_NAME} SHARED ${SOURCES})
