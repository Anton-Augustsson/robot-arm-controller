#include "mg996r.hpp" 
#include "../utils/conversion.hpp" 

Mg996r::Mg996r(MotorParameters motorParameters) {
  setMotorParameters(motorParameters);
  pwm = param.pwmRange.min;
}

void Mg996r::setMotorParameters(MotorParameters motorParameters) {
  param = motorParameters;
}

void Mg996r::setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) {
  param.pwmRange = {pwmMin, pwmMax};
}

MotorParameters Mg996r::getMotorParameters() {
  return param;
}

void Mg996r::setMotorAngle(uint8_t angle) {
  pwm = conversion::angleToPwm(angle, param.angleRange, param.pwmRange);
}

uint8_t Mg996r::getMotorAngle() {
  return conversion::pwmToAngle(pwm, param.angleRange, param.pwmRange);
}