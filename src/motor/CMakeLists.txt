add_library(
    motor
    "${CMAKE_CURRENT_SOURCE_DIR}/conversion.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/conversion.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/motor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/motor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/motor_type.hpp"
)

target_include_directories(motor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(NOT SIMULATION) 
    target_link_libraries(motor pico_stdlib hardware_pwm)
endif()