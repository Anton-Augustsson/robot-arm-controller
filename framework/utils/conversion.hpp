#ifndef conversion_HPP
#define conversion_HPP

#include "types.hpp"

namespace conversion {
  uint8_t angleToPwm(uint8_t angle, AngleRange angleRange, PwmRange pwmRange);
  uint8_t pwmToAngle(uint8_t pwm, AngleRange angleRange, PwmRange pwmRange);
}

#endif