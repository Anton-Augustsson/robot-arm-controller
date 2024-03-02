add_library(
    states
    "${CMAKE_CURRENT_SOURCE_DIR}/states.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/manual.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/calibration.cpp"
)

target_include_directories(states PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})