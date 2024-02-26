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


class Mg996r: public ServoMotor {
  public:
    Mg996r (ServoMotorParameters motorParameters) {
      setMotorParameters(motorParameters);
      pwm = param.pwmMin;
    }

    void setMotorParameters(ServoMotorParameters motorParameters) override {
      param = motorParameters;
    }

    ServoMotorParameters getMotorParameters() override {
      return param;
    }

    void setMotorAngle(uint8_t angle) override {
      pwm = angleToPwm(angle);
    }

    uint8_t getMotorAngle() override {
      return pwmToAngle(pwm);
    }

  private:
    ServoMotorParameters param;
    uint8_t pwm;

    uint8_t angleToPwm(uint8_t angle) {
      return static_cast<uint8_t>(std::round(
        (angle - param.angleMin) * (param.pwmMax - param.pwmMin)
        / (param.angleMax - param.angleMin) + param.pwmMin));
    }

    uint8_t pwmToAngle(uint8_t pwm) {
      return static_cast<uint8_t>(std::round(
        (pwm - param.pwmMin) * (param.angleMax - param.angleMin)
        / (param.pwmMax - param.pwmMin) + param.angleMin));
    }
};

int main(void) {
  ServoMotorParameters motorParameters1 {
    "mg99r", 1, 3, 12, 0, 90
  };

  Mg996r motor1(motorParameters1);

  int angle = motor1.getMotorAngle();
  std::cout << "Motor angle: " << angle << std::endl;
 
  motor1.setMotorAngle(0);
  angle = motor1.getMotorAngle();
  std::cout << "Motor angle: " << angle << std::endl;

  motor1.setMotorAngle(40);
  angle = motor1.getMotorAngle();
  std::cout << "Motor angle: " << angle << std::endl;

  motor1.setMotorAngle(90);
  angle = motor1.getMotorAngle();
  std::cout << "Motor angle: " << angle << std::endl;
}