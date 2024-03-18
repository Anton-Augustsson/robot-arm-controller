#include "context.hpp" 

ContextSingleton* ContextSingleton::pinstance_{nullptr};
std::mutex ContextSingleton::mutex_;

ContextSingleton *ContextSingleton::GetInstance(const std::string& value)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new ContextSingleton(value);
    }
    return pinstance_;
}

