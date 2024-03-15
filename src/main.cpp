#include "motor/mg996r.hpp" 
#include "motor/servo_motor.hpp" 
#include "utils/types.hpp" 
#include "utils/config.hpp" 
#include "states/states.hpp" 

#include <fstream>
#include <chrono>
#include <thread>
#include <array>
#include <cassert>
#include <mutex>
#include <queue>
#include <condition_variable>


// TODO: move queue to utils. Should maybe be called EventQueue
// FIXME: risk for stack overflow if someone continuously push and no one pop. Should have fixed size
template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {}

    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        condition_.notify_one(); // Notify waiting threads that new data is available
    }

    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return false;
        }
        value = queue_.front();
        queue_.pop();
        return true;
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });
        value = queue_.front();
        queue_.pop();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

ThreadSafeQueue<event_t> event_queue;

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
  state_t current_state = state_cal;
  state_t prev_state = state_cal;

  for(int i = 0; i < 10; i++) {
    current_state.Enter();
    event_queue.wait_and_pop(evt);

    if(current_state.state_type == periodic_st) {
      // FIXME: (with wait_and_pop in beginning) if you only have one event that makes you change, you will not do Do() Since the while statement is not true
      // (no wait_and_pop in beginning) you will still have the same event that made you switch, thus switching back and forth
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        std::this_thread::sleep_for(std::chrono::milliseconds(current_state.delay_ms));
        event_queue.try_pop(evt);
      }
    } else {
      while(current_state.id == state_table[current_state.id][evt].id) {
        current_state.Do();
        event_queue.wait_and_pop(evt);
      }
    }

    current_state.Exit();
    prev_state = current_state;
    current_state = state_table[current_state.id][evt];
  }
}

void testStateTable() {
  // TODO: verify which state you should be in
  event_queue.push(b1_evt); // cal
  event_queue.push(b1_evt); // cal
  event_queue.push(no_evt); // cal
  event_queue.push(b2_evt); // cal
  event_queue.push(b3_evt); // cal
  event_queue.push(b4_evt); // man
  event_queue.push(b4_evt); // cal
  event_queue.push(b1_evt); // cal
  event_queue.push(b1_evt); // cal
  event_queue.push(b2_evt); // cal
  event_queue.push(b2_evt); // cal

  event_queue.empty();
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