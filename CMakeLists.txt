cmake_minimum_required(VERSION 3.15)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(SolarSystem main.cpp)

target_link_libraries(SolarSystem -lglut -lGL -lGLU)
