#include <chrono>
#include <thread>
#include "mock.hpp"
#include "sim_context_singleton.hpp"

void stdio_init_all() {
  return;
}

void sleep_ms(unsigned int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
