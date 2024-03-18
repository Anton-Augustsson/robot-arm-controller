add_library(
    states
    "${CMAKE_CURRENT_SOURCE_DIR}/states.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/calibration.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/idle.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/manual.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/move_to_start.cpp"
)

target_include_directories(states PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})