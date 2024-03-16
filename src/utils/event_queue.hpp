#ifndef EventQueue_HPP
#define EventQueue_HPP

#include "types.hpp" 

#include <mutex>
#include <queue>
#include <condition_variable>

class EventQueue {
public:
    EventQueue() {}

    void push(const event_t& value);
    bool try_pop(event_t& value);
    void wait_and_pop(event_t& value);
    bool empty() const;

private:
    std::queue<event_t> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};

#endif