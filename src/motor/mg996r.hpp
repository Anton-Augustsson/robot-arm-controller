#ifndef Mg996r_HPP
#define Mg996r_HPP

#include "servo_motor.hpp" 
#include <iostream>

class Mg996r: public ServoMotor {
  public:
    Mg996r(ServoMotorParameters motorParameters);
    void setMotorParameters(ServoMotorParameters motorParameters) override;
    void setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) override;
    ServoMotorParameters getMotorParameters() override;
    void setMotorAngle(uint8_t angle) override;
    uint8_t getMotorAngle() override;

  private:
    ServoMotorParameters param;
    uint8_t pwm;
};

#endif