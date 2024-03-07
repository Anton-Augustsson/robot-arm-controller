#ifndef types_HPP
#define types_HPP

#include <cstdint>
#include <string>

struct AngleRange {
  uint8_t min;
  uint8_t max;
};

struct PwmRange {
  uint8_t min;
  uint8_t max;
};

struct MotorParameters {
    std::string model;
    uint8_t id;
    PwmRange pwmRange;
    AngleRange angleRange;
};

#endif