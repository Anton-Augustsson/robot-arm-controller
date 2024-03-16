#include "motor/mg996r.hpp" 
#include "motor/servo_motor.hpp" 
#include "utils/types.hpp" 
#include "utils/config.hpp" 
#include "utils/event_queue.hpp" 
#include "states/states.hpp" 

#include <fstream>
#include <chrono>
#include <thread>
#include <array>
#include <cassert>


// TODO: move queue to utils. Should maybe be called EventQueue


EventQueue event_queue;

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

void runStateTable() {
  event_t evt = no_evt;
  state_t current_state = state_idl;

  for(;;) {
    current_state.Enter();

    if(current_state.state_type == periodic_st) {
      if(!event_queue.try_pop(evt)) {
        evt = no_evt;
      }
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        std::this_thread::sleep_for(std::chrono::milliseconds(current_state.delay_ms));
        event_queue.try_pop(evt);
      }
    } else {
      event_queue.wait_and_pop(evt);
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        event_queue.wait_and_pop(evt);
      }
    }

    current_state.Exit();
    current_state = state_table[current_state.id][evt];
  }
}

void testStateTable() {
  // TODO: verify which state you should be in
                            // idl
  event_queue.push(b4_evt); // cal
  event_queue.push(b1_evt); // cal
  event_queue.push(no_evt); // cal
  event_queue.push(b2_evt); // cal
  event_queue.push(b3_evt); // cal
  event_queue.push(b4_evt); // man
  event_queue.push(b4_evt); // mts
  event_queue.push(b1_evt); // idle
  event_queue.push(b1_evt); // idle
  event_queue.push(b2_evt); // man
  event_queue.push(b2_evt); // man
  event_queue.push(b4_evt); // mts
                            // mts
                            // mts
                            // mts
}

int main(void) {
  MotorParameters motorParameters0 = config::readMotorParameters(0);
  MotorParameters motorParameters1 = config::readMotorParameters(1);
  MotorParameters motorParameters2 = config::readMotorParameters(2);
  MotorParameters motorParameters3 = config::readMotorParameters(3);

  const size_t numMotors = 4;
  std::array<Mg996r*, numMotors> motors = {
    new Mg996r(motorParameters0),
    new Mg996r(motorParameters1),
    new Mg996r(motorParameters2),
    new Mg996r(motorParameters3),
  };
  

  std::thread t1(runStateTable);

  testMg996r(motors[0]);
  testStateTable();

  t1.join();

  for (auto motor : motors) {
    delete motor;
  }
}