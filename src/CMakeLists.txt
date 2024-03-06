cmake_minimum_required(VERSION 3.13)
project(sample C CXX ASM)
cmake_policy(SET CMP0135 NEW)
set(DOWNLOAD_EXTRACT_TIMESTAMP 1)

add_executable(smotor main.cpp)
add_subdirectory(motor)
add_subdirectory(states)
add_subdirectory(utils)

target_link_libraries(smotor PUBLIC motor states utils)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(smotor PRIVATE nlohmann_json::nlohmann_json)
