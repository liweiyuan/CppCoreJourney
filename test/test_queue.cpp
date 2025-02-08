#include "safe_queue.hpp"
#include <gtest/gtest.h>
#include <string>
#include <thread>

class SafeQueueTest : public ::testing::Test {
  protected:
    SafeQueue<int> intQueue;
    SafeQueue<std::string> stringQueue;

    void SetUp() override {
        intQueue.push(1);
        intQueue.push(2);
        stringQueue.push("Hello");
        stringQueue.push("World");
    }
};

TEST_F(SafeQueueTest, PushAndPop) {
    intQueue.push(3);
    EXPECT_EQ(intQueue.pop(), 1);
    EXPECT_EQ(intQueue.pop(), 2);
    EXPECT_EQ(intQueue.pop(), 3);

    stringQueue.push("!");
    EXPECT_EQ(stringQueue.pop(), "Hello");
    EXPECT_EQ(stringQueue.pop(), "World");
    EXPECT_EQ(stringQueue.pop(), "!");
}

TEST_F(SafeQueueTest, IsEmpty) {
    SafeQueue<int> emptyQueue;
    EXPECT_TRUE(emptyQueue.isEmpty());

    intQueue.pop();
    intQueue.pop();
    EXPECT_TRUE(intQueue.isEmpty());
}

TEST_F(SafeQueueTest, Size) {
    EXPECT_EQ(intQueue.size(), 2);
    intQueue.push(3);
    EXPECT_EQ(intQueue.size(), 3);

    EXPECT_EQ(stringQueue.size(), 2);
    stringQueue.push("!");
    EXPECT_EQ(stringQueue.size(), 3);
}

TEST_F(SafeQueueTest, Clear) {
    intQueue.clear();
    EXPECT_TRUE(intQueue.isEmpty());

    stringQueue.clear();
    EXPECT_TRUE(stringQueue.isEmpty());
}

TEST_F(SafeQueueTest, ConcurrentAccess) {

    SafeQueue<int> queue;
    std::thread t1([&]() {
        for (int i = 0; i < 100; ++i) {
            queue.push(i);
        }
    });

    std::thread t2([&]() {
        for (int i = 0; i < 100; ++i) {
            queue.pop();
        }
    });

    t1.join();
    t2.join();
    EXPECT_TRUE(queue.isEmpty());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
