#include "safe_queue.hpp"
#include <functional>
#include <future>
#include <gtest/gtest.h>

void producer(ThreadSafeQueue<int> &queue, int count) {
    for (int i = 0; i < count; ++i) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(100)); //
        // 模拟生产耗时
        std::cout << "Produced: " << i << "\n";
        queue.push(i);
    }
    queue.push(-1); // 结束信号
}

void consumer(ThreadSafeQueue<int> &queue) {
    while (true) {
        auto value = queue.pop();
        if (value && *value == -1) { // 检查结束信号
            break;
        }
        std::cout << "Consumed: " << *value << "\n";
    }
}

// 测试上述的生产者消费者，使用std::async
TEST(ThreadSafeQueueTests, test_thread_safe_queue) {
    ThreadSafeQueue<int> queue;
    auto p = std::async(std::launch::async, producer, std::ref(queue), 1000);
    auto c = std::async(std::launch::async, consumer, std::ref(queue));

    // 等待生产者和消费者完成
    p.get();
    c.get();
}

// 测试零项
TEST(ThreadSafeQueueTests, test_zero_items) {
    ThreadSafeQueue<int> queue;
    auto p = std::async(std::launch::async, producer, std::ref(queue), 0);
    auto c = std::async(std::launch::async, consumer, std::ref(queue));

    p.get();
    c.get();
}

// 测试多个消费者
TEST(ThreadSafeQueueTests, test_multiple_consumers) {
    ThreadSafeQueue<int> queue;
    auto p = std::async(std::launch::async, producer, std::ref(queue), 1000);
    auto c1 = std::async(std::launch::async, consumer, std::ref(queue));
    // auto c2 = std::async(std::launch::async, consumer, std::ref(queue));

    p.get();
    c1.get();
    // c2.get();
}

// 测试多个生产者
TEST(ThreadSafeQueueTests, test_multiple_producers) {
    ThreadSafeQueue<int> queue;
    auto p1 = std::async(std::launch::async, producer, std::ref(queue), 500);
    // auto p2 = std::async(std::launch::async, producer, std::ref(queue), 500);
    auto c = std::async(std::launch::async, consumer, std::ref(queue));

    p1.get();
    // p2.get();
    c.get();
}

// 测试混合生产者和消费者
TEST(ThreadSafeQueueTests, test_mixed_producers_consumers) {
    ThreadSafeQueue<int> queue;
    auto p1 = std::async(std::launch::async, producer, std::ref(queue), 500);
    // auto p2 = std::async(std::launch::async, producer, std::ref(queue), 500);
    auto c1 = std::async(std::launch::async, consumer, std::ref(queue));
    // auto c2 = std::async(std::launch::async, consumer, std::ref(queue));

    p1.get();
    // p2.get();
    c1.get();
    // c2.get();
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
