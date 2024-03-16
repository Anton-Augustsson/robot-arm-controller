#ifndef TestMotors_HPP
#define TestMotors_HPP

#include <cassert>

void testMg996r(Mg996r* motor) {
  int angle = motor->getMotorAngle();
  assert(angle == 0);

  motor->setMotorAngle(0);
  angle = motor->getMotorAngle();
  assert(angle == 0);

  motor->setMotorAngle(40);
  angle = motor->getMotorAngle();
  assert(angle == 40);

  motor->setMotorAngle(90);
  angle = motor->getMotorAngle();
  assert(angle == 90);
}

#endif