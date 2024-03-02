#include "motor/mg996r.hpp" 
#include "utils/types.hpp" 
#include "states/states.hpp" 

#include <chrono>
#include <thread>

// TODO: interrupt service routine (isr)
// TODO: use std::counting_semaphore in the isr
// TODO: typedef enum _event_t

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

  uint8_t evt;
  state_t current_state = state_cal;

  current_state.Enter();

  current_state.Do();
  std::this_thread::sleep_for(std::chrono::milliseconds(current_state.delay_ms));
  evt = 1;

  current_state.Exit();
  current_state = state_table[current_state.id][evt];
}