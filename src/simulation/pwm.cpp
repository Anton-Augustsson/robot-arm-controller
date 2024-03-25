#include "mock.hpp"

void pwm_set_clkdiv(unsigned int slice_num, float divider) {
  return;
}
void pwm_set_wrap(unsigned int slice_num, int wrap) {
  return;
}

unsigned int pwm_gpio_to_slice_num(unsigned int gpio) {
  return 1;
}

void pwm_set_enabled(unsigned int slice_num, bool enable) {
  return;
}

void pwm_set_chan_level(unsigned int slice_num, unsigned int chan, int level) {
  return;
}


