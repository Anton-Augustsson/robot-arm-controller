#ifndef motor_type_HPP
#define motor_type_HPP

#include <stdint.h>
#include <string>

struct AngleRange {
  uint8_t min;
  uint8_t max;
};

struct PwmRange {
  uint8_t min;
  uint8_t max;
};
typedef enum _motor_id_t {
    m0 = 0,
    m1 = 1,
    m2 = 2,
    m3 = 3,
    m4 = 4,
    m5 = 5
} motor_id_t;

struct MotorParameters {
    std::string model;
    motor_id_t id;
    uint8_t gpio;
    PwmRange pwmRange; // TODO: change to uint16_t
    AngleRange angleRange;
};

#endif