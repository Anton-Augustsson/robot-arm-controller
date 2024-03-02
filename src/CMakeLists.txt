cmake_minimum_required(VERSION 3.13)
project(sample C CXX ASM)

add_executable(smotor main.cpp)
add_subdirectory(motor)
add_subdirectory(utils)

target_link_libraries(smotor PUBLIC motor utils)
