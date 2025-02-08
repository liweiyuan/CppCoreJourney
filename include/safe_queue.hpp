#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
template <typename T> class ThreadSafeQueue {
private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_var_;

public:
  void push(const T &value) {
    {
      std::lock_guard<std::mutex> lock(mutex_);
      queue_.push(value);
    }
    cond_var_.notify_all();
  }

  std::optional<T> pop() {
    std::unique_lock<std::mutex> lock(mutex_);
    cond_var_.wait(lock, [this] { return !queue_.empty(); });
    if (queue_.empty()) {
      return std::nullopt;
    }
    T value = queue_.front();
    queue_.pop();
    return value;
  }
};
#endif