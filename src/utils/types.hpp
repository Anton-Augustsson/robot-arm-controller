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
    m1 = 0,
    m2 = 1,
    m3 = 2,
    m4 = 3,
    m5 = 4
} motor_id_t;

struct MotorParameters {
    std::string model;
    motor_id_t id;
    PwmRange pwmRange;
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