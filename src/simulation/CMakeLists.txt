add_library(
    simulation
    "${CMAKE_CURRENT_SOURCE_DIR}/sim_context_singleton.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sim_context_singleton.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mock.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/bi.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gpio.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pwm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/spi.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/stdio.cpp"
)

target_include_directories(simulation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})