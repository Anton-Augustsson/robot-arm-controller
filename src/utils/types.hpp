#ifndef types_HPP
#define types_HPP

#include <cstdint>
#include <string>
#include <chrono>

struct AngleRange {
  uint8_t min;
  uint8_t max;
};

struct PwmRange {
  uint8_t min;
  uint8_t max;
};

typedef enum _led_id_t {
    led1 = 0
} led_id_t;

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

typedef enum _event_t {
    b1_evt = 0,
    b2_evt = 1,
    b3_evt = 2,
    b4_evt = 3,
    no_evt = 4
} event_t;

typedef enum _state_type_t {
    event_driven_st = 0,
    periodic_st = 1
} state_type_t;

struct Record {
  std::time_t time;
  std::string msg;
};

#endif