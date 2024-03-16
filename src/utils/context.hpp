#ifndef Context_HPP
#define Context_HPP

#include "thread_safe_queue.hpp" 
#include "types.hpp" 

// Only threadsafe objects are mutable to prevent data races caused by shared memory between threads.
struct Context {
  int configParam1;
  double configParam2;
  
  ThreadSafeQueue<event_t> event_queue;
  ThreadSafeQueue<Record> log_queue;

  Context();
};

extern Context context;

#endif