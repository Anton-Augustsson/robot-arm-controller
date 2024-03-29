#include <cassert>
#include <iostream>
#include "mock.hpp"
#include "../simulation/sim_context_singleton.hpp" 

void printMotorStatus(unsigned int gpio_or_slice_num) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  std::cout << "PWM GPIO " << gpio_or_slice_num << " " 
            << statusPwmToString(simContext->getMotorStatus(gpio_or_slice_num)) << std::endl;
}

unsigned int pwm_gpio_to_slice_num(unsigned int gpio) {
  return gpio; // For simulation slice_num and gpio is the same
}

void pwm_set_clkdiv(unsigned int slice_num, float divider) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  simContext->setMotorStatus(slice_num, Status_pwm::CLKDIV_SET);
  printMotorStatus(slice_num);
}

void pwm_set_wrap(unsigned int slice_num, int wrap) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  assert(simContext->getMotorStatus(slice_num) == Status_pwm::CLKDIV_SET);
  simContext->setMotorStatus(slice_num, Status_pwm::WRAP_SET);
  printMotorStatus(slice_num);
}

void pwm_set_enabled(unsigned int slice_num, bool enable) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  assert(simContext->getMotorStatus(slice_num) == Status_pwm::WRAP_SET);
  simContext->setMotorStatus(slice_num, Status_pwm::ENABLED);
  printMotorStatus(slice_num);
}

void pwm_set_chan_level(unsigned int slice_num, unsigned int chan, int level) {
  SimContextSingleton* simContext = SimContextSingleton::GetInstance();
  assert(simContext->getMotorStatus(slice_num) == Status_pwm::WRAP_SET
      || simContext->getMotorStatus(slice_num) == Status_pwm::ENABLED
      || simContext->getMotorStatus(slice_num) == Status_pwm::CHAN_LEVEL_SET);
  simContext->setMotorStatus(slice_num, Status_pwm::CHAN_LEVEL_SET);
  printMotorStatus(slice_num);
}
