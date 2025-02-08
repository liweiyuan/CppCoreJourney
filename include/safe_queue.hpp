#ifndef SAFE_QUEUE_HPP
#define SAFE_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T> class SafeQueue {
  public:
    SafeQueue() = default;
    ~SafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cond_var.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cond_var.wait(lock, [this] { return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        std::queue<T> empty;
        std::swap(queue, empty);
    }

  private:
    mutable std::mutex mtx;
    std::queue<T> queue;
    std::condition_variable cond_var;
};

#endif // SAFE_QUEUE_HPP
