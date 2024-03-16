#include "event_queue.hpp" 


void EventQueue::push(const event_t& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(value);
    condition_.notify_one(); // Notify waiting threads that new data is available
}

bool EventQueue::try_pop(event_t& value) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return false;
    }
    value = queue_.front();
    queue_.pop();
    return true;
}

void EventQueue::wait_and_pop(event_t& value) {
    std::unique_lock<std::mutex> lock(mutex_);
    condition_.wait(lock, [this] { return !queue_.empty(); });
    value = queue_.front();
    queue_.pop();
}

bool EventQueue::empty() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return queue_.empty();
}