#include "mock.hpp"
#include <chrono>
#include <thread>

void stdio_init_all() {
  return;
}

void sleep_ms(unsigned int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
