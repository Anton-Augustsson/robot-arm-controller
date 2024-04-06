#ifndef Context_HPP
#define Context_HPP

#include "thread_safe_queue.hpp" 
#include "types.hpp" 

#include <mutex>

class ContextSingleton {
  private:
    static ContextSingleton* pinstance_;
    static std::mutex mutex_;

    // TODO: replace with usable context data
    int configParam1;
    double configParam2;

  protected:
    ContextSingleton(const std::string value): value_(value) {}
    ~ContextSingleton() {}
    std::string value_;

  public:
    ContextSingleton(ContextSingleton &other) = delete;
    void operator=(const ContextSingleton &) = delete;
    static ContextSingleton *GetInstance(const std::string& value);

    ThreadSafeQueue<event_t>* event_queue = new ThreadSafeQueue<event_t>();
    ThreadSafeQueue<Record>* log_queue = new ThreadSafeQueue<Record>();

    std::string value() const {
        return value_;
    } 
};

#endif