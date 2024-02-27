#include "mg996r.hpp" 

Mg996r::Mg996r(ServoMotorParameters motorParameters) {
  setMotorParameters(motorParameters);
  pwm = param.pwmMin;
}

void Mg996r::setMotorParameters(ServoMotorParameters motorParameters) {
  param = motorParameters;
}

ServoMotorParameters Mg996r::getMotorParameters() {
  return param;
}

void Mg996r::setMotorAngle(uint8_t angle) {
  pwm = angleToPwm(angle);
}

uint8_t Mg996r::getMotorAngle() {
  return pwmToAngle(pwm);
}

uint8_t Mg996r::angleToPwm(uint8_t angle) {
  return static_cast<uint8_t>(std::round(
    (angle - param.angleMin) * (param.pwmMax - param.pwmMin)
    / (param.angleMax - param.angleMin) + param.pwmMin));
}

uint8_t Mg996r::pwmToAngle(uint8_t pwm) {
  return static_cast<uint8_t>(std::round(
    (pwm - param.pwmMin) * (param.angleMax - param.angleMin)
    / (param.pwmMax - param.pwmMin) + param.angleMin));
}