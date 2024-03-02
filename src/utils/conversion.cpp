#include "conversion.hpp"
#include <cmath>

uint8_t conversion::angleToPwm(uint8_t angle, AngleRange angleRange, PwmRange pwmRange){
  return static_cast<uint8_t>(std::round(
    (angle - angleRange.min) * (pwmRange.max - pwmRange.min)
    / (angleRange.max - angleRange.min) + pwmRange.min));
}

uint8_t conversion::pwmToAngle(uint8_t pwm, AngleRange angleRange, PwmRange pwmRange){
  return static_cast<uint8_t>(std::round(
    (pwm - pwmRange.min) * (angleRange.max - angleRange.min)
    / (pwmRange.max - pwmRange.min) + angleRange.min));
}