#include "motor/mg996r.hpp" 
#include "motor/servo_motor.hpp" 
#include "utils/types.hpp" 
#include "utils/config.hpp" 
#include "utils/context.hpp" 
#include "states/states.hpp" 
#include "tests/test_motors.hpp" 
#include "tests/test_state_table.hpp" 

#include <fstream>
#include <thread>
#include <array>

void runStateTable() {
  ContextSingleton* context = ContextSingleton::GetInstance("FOO");
  event_t evt = no_evt;
  state_t current_state = state_idl;

  for(;;) {
    current_state.Enter();

    if(current_state.state_type == periodic_st) {
      if(!context->event_queue->try_pop(evt)) {
        evt = no_evt;
      }
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        std::this_thread::sleep_for(std::chrono::milliseconds(current_state.delay_ms));
        context->event_queue->try_pop(evt);
      }
    } else {
      context->event_queue->wait_and_pop(evt);
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        context->event_queue->wait_and_pop(evt);
      }
    }

    current_state.Exit();
    current_state = state_table[current_state.id][evt];
  }
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