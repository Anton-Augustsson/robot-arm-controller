#ifndef config_HPP
#define config_HPP

#include "types.hpp"

namespace config {
  MotorParameters readMotorParameters(int motorNum);
  void saveMotor(MotorParameters motorParameters);
}

#endif