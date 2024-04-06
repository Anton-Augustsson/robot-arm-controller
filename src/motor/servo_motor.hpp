#ifndef ServoMotor_HPP
#define ServoMotor_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../utils/types.hpp"

class ServoMotor {
  public:
    virtual void setMotorParameters(MotorParameters motorParameters) = 0;
    virtual void setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) = 0;
    virtual MotorParameters getMotorParameters() = 0;
    virtual void setMotorAngle(uint8_t angle) = 0;
    virtual void setMotorDutyCycle(uint16_t dutyCycle) = 0;
    virtual uint8_t getMotorAngle() = 0;

    virtual ~ServoMotor() {}
};

#endif