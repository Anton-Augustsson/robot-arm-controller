#ifndef Mg996r_HPP
#define Mg996r_HPP

#include "servo_motor.hpp" 
#include "../utils/types.hpp" 

#include <iostream>

class Mg996r: public ServoMotor {
  public:
    Mg996r(MotorParameters motorParameters);
    void setMotorParameters(MotorParameters motorParameters) override;
    void setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) override;
    MotorParameters getMotorParameters() override;
    void setMotorAngle(uint8_t angle) override;
    void setMotorDutyCycle(uint16_t dutyCycle) override;
    uint8_t getMotorAngle() override;

  private:
    MotorParameters param;
    uint8_t slice_num;
    uint8_t pwm;
};

#endif