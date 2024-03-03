#include "motor/mg996r.hpp" 
#include "motor/servo_motor.hpp" 
#include "utils/types.hpp" 
#include "states/states.hpp" 

#include <chrono>
#include <thread>
#include <array>
#include <cassert>

// TODO: interrupt service routine (isr)
// TODO: use std::counting_semaphore in the isr
// TODO: typedef enum _event_t

void testMg996r(Mg996r* motor) {
  int angle = motor->getMotorAngle();
  assert(angle == 0);

  motor->setMotorAngle(0);
  angle = motor->getMotorAngle();
  assert(angle == 0);

  motor->setMotorAngle(40);
  angle = motor->getMotorAngle();
  assert(angle == 40);

  motor->setMotorAngle(90);
  angle = motor->getMotorAngle();
  assert(angle == 90);
}

void testStateTable() {
  uint8_t evt;
  state_t current_state = state_cal;

  current_state.Enter();

  current_state.Do();
  std::this_thread::sleep_for(std::chrono::milliseconds(current_state.delay_ms));
  evt = 1;

  current_state.Exit();
  current_state = state_table[current_state.id][evt];
}

int main(void) {
  // FIXME: read from calibration file
  ServoMotorParameters motorParameters1 {"mg996r", 1, {3, 12}, {0, 90}};
  ServoMotorParameters motorParameters2 {"mg996r", 2, {3, 12}, {0, 90}};
  ServoMotorParameters motorParameters3 {"mg996r", 3, {3, 12}, {0, 90}};
  ServoMotorParameters motorParameters4 {"mg996r", 4, {3, 12}, {0, 90}};

  const size_t numMotors = 4;
  std::array<Mg996r*, numMotors> motors = {
    new Mg996r(motorParameters1),
    new Mg996r(motorParameters2),
    new Mg996r(motorParameters3),
    new Mg996r(motorParameters4),
  };
  
  testMg996r(motors[0]);
  testStateTable();

  for (auto motor : motors) {
    delete motor;
  }
}