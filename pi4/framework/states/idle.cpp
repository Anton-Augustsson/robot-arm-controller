#include <iostream>
#include "states.hpp"

void do_state_idle(void) {
  std::cout << "do_state_idle" << std::endl;
}

void enter_state_idle(void) {
  std::cout << "enter_state_idle" << std::endl;
}

void exit_state_idle(void) {
  std::cout << "exit_state_idle" << std::endl;
}


