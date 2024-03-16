#include "config.hpp"
#include "constants.hpp"
#include "types.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <iostream>

using json = nlohmann::json;

MotorParameters jsonToMotorParameters(json motor) {
  return MotorParameters {
    motor["MotorType"],
    motor["ID"],
    PwmRange {
      motor["PWM"]["Min"],
      motor["PWM"]["Max"],
    },
    AngleRange {
      motor["AngleRange"]["Min"],
      motor["AngleRange"]["Max"],
      },
  };
}

MotorParameters config::readMotorParameters(int motorNum) {
  std::ifstream f(constants::config);
  json data = json::parse(f);

  std::string motorName = "Motor" + std::to_string(motorNum);
  std::cout << motorName << std::endl;
  json motor = data["Motors"][motorName];
  MotorParameters result = jsonToMotorParameters(motor);

  f.close();
  return result;
}

void config::saveMotor(MotorParameters motorParameters) {
  // TODO:
  return;
}