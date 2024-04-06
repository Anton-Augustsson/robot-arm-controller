#ifndef Mg996r_HPP
#define Mg996r_HPP

#include <iostream>
#include "motor_type.hpp"

class Motor {
  public:
    Motor(MotorParameters motorParameters);
    void setMotorParameters(MotorParameters motorParameters);
    void setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax);
    MotorParameters getMotorParameters();
    void setMotorAngle(uint8_t angle);
    void setMotorDutyCycle(uint16_t dutyCycle);
    uint8_t getMotorAngle();

  private:
    MotorParameters param;
    uint8_t slice_num;
    uint8_t pwm;
};

#endif