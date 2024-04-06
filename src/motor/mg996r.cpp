#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mg996r.hpp" 
#include "../utils/conversion.hpp" 

#ifdef SIMULATION_ENABLED
#include "../simulation/mock.hpp"
#else
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#endif

#define MAX_DUTY_CYCLE 65535 // 2^16-1
#define PWM_FREQUENCY 2500 // 50 Hz (2500 us period)

Mg996r::Mg996r(MotorParameters motorParameters) {
  setMotorParameters(motorParameters);

  gpio_set_function(param.gpio, GPIO_FUNC_PWM); // m1 works
  slice_num = pwm_gpio_to_slice_num(param.gpio);
  pwm_set_clkdiv(slice_num, PWM_FREQUENCY); 
  pwm_set_wrap(slice_num, MAX_DUTY_CYCLE);
  pwm_set_enabled(slice_num, true);

  // TODO: init pwm
  pwm = param.pwmRange.min; // TODO: duty cycle should be the in between min and max
}

void Mg996r::setMotorParameters(MotorParameters motorParameters) {
  param = motorParameters;
}

void Mg996r::setMotorPwmCalibration(uint8_t pwmMin, uint8_t pwmMax) {
  param.pwmRange = {pwmMin, pwmMax};
}

MotorParameters Mg996r::getMotorParameters() {
  return param;
}

void Mg996r::setMotorAngle(uint8_t angle) {
  pwm = conversion::angleToPwm(angle, param.angleRange, param.pwmRange);
}

void Mg996r::setMotorDutyCycle(uint16_t dutyCycle) {
  pwm_set_chan_level(slice_num, PWM_CHAN_A, dutyCycle);
}

uint8_t Mg996r::getMotorAngle() {
  return conversion::pwmToAngle(pwm, param.angleRange, param.pwmRange);
}