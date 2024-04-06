cmake_minimum_required(VERSION 3.13)


option(SIMULATION "Run with mock functions instead of pico library" OFF)

if(SIMULATION) 
  project(sample C CXX ASM)

  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)

  add_compile_definitions(SIMULATION_ENABLED)

  add_executable(sample main.cpp)

  add_subdirectory(src/motor)
  add_subdirectory(src/simulation)

  target_link_libraries(sample PUBLIC motor simulation)

else()
  include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
  project(sample C CXX ASM)

  set(CMAKE_C_COMPILER /usr/bin/arm-none-eabi-gcc CACHE PATH "" FORCE)
  set(CMAKE_CXX_COMPILER /usr/bin/arm-none-eabi-g++ CACHE PATH "" FORCE)

  set(CMAKE_C_STANDARD 11)
  set(CMAKE_CXX_STANDARD 17)

  pico_sdk_init()

  add_executable(sample main.cpp)

  pico_enable_stdio_usb(sample 1)
  pico_enable_stdio_uart(sample 1)
  pico_add_extra_outputs(sample)

  add_subdirectory(src/motor)

  target_link_libraries(sample PUBLIC pico_stdlib motor hardware_spi hardware_pwm)
endif()