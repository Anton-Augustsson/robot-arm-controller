#include "motor/mg996r.hpp" 
#include "utils/types.hpp" 

int main(void) {
  ServoMotorParameters motorParameters1 {
    "mg996r", 1, {3, 12}, {0, 90}
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