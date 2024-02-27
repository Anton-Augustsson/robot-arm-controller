#ifndef Mg996r_HPP
#define Mg996r_HPP

#include "servo_motor.hpp" 
#include <iostream>

class Mg996r: public ServoMotor {
  public:
    Mg996r(ServoMotorParameters motorParameters);
    void setMotorParameters(ServoMotorParameters motorParameters) override;
    ServoMotorParameters getMotorParameters() override;
    void setMotorAngle(uint8_t angle) override;
    uint8_t getMotorAngle() override;

  private:
    ServoMotorParameters param;
    uint8_t pwm;
    uint8_t angleToPwm(uint8_t angle);
    uint8_t pwmToAngle(uint8_t pwm);
};

#endif