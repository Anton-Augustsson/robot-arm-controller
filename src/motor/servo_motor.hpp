#ifndef ServoMotor_HPP
#define ServoMotor_HPP

#include <iostream>
#include <string>
#include <vector>

#include "../utils/types.hpp"

struct ServoMotorParameters {
    std::string model;
    uint8_t id;
    PwmRange pwmRange;
    AngleRange angleRange;
};

class ServoMotor {
  public:
    virtual void setMotorParameters(ServoMotorParameters motorParameters) = 0;
    virtual void setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) = 0;
    virtual ServoMotorParameters getMotorParameters() = 0;
    virtual void setMotorAngle(uint8_t angle) = 0;
    virtual uint8_t getMotorAngle() = 0;

    virtual ~ServoMotor() {}
};

#endif