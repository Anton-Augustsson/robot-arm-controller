add_library(
    motor
    "${CMAKE_CURRENT_SOURCE_DIR}/servo_motor.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mg996r.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mg996r.cpp"
)

target_include_directories(motor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(SIMULATION) 
else()
    target_link_libraries(motor pico_stdlib hardware_pwm)
endif()