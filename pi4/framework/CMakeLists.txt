cmake_minimum_required(VERSION 3.13)
project(sample C CXX ASM)
cmake_policy(SET CMP0135 NEW)
set(DOWNLOAD_EXTRACT_TIMESTAMP 1)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Release or Debug)" FORCE)
endif()

# Add compiler flags for debugging only in Debug build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

add_executable(smotor main.cpp)
add_subdirectory(motor)
add_subdirectory(states)
add_subdirectory(utils)

target_link_libraries(smotor PUBLIC motor states utils)