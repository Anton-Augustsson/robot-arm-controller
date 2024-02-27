#ifndef ServoMotor_HPP
#define ServoMotor_HPP

#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <vector>

struct ServoMotorParameters {
    std::string model;
    uint8_t id;
    uint8_t pwmMin;
    uint8_t pwmMax;
    uint8_t angleMin;
    uint8_t angleMax;
};

class ServoMotor {
  public:
    virtual void setMotorParameters(ServoMotorParameters motorParameters) = 0;
    virtual ServoMotorParameters getMotorParameters() = 0;
    virtual void setMotorAngle(uint8_t angle) = 0;
    virtual uint8_t getMotorAngle() = 0;

    virtual ~ServoMotor() {}
};

#endif