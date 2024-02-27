cmake_minimum_required(VERSION 3.13)
project(sample C CXX ASM)

add_executable(smotor main.cpp)
target_include_directories(smotor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(smotor PRIVATE servo_motor.hpp mg996r.hpp mg996r.cpp)
