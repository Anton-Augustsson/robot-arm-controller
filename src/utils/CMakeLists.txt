add_library(
    utils
    "${CMAKE_CURRENT_SOURCE_DIR}/types.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/conversion.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/conversion.cpp"
)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})