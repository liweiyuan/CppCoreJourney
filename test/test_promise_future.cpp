#include <chrono>
#include <future>
#include <gtest/gtest.h>
#include <thread>

class PromiseFutureTest : public ::testing::Test {
  protected:
    std::promise<int> promise;
    std::future<int> future;

    void SetUp() override { future = promise.get_future(); }
};

TEST_F(PromiseFutureTest, SetValue) {
    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        promise.set_value(42);
    });

    EXPECT_EQ(future.get(), 42);
    t.join();
}

TEST_F(PromiseFutureTest, SetException) {
    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        promise.set_exception(
            std::make_exception_ptr(std::runtime_error("error")));
    });

    EXPECT_THROW(future.get(), std::runtime_error);
    t.join();
}

TEST_F(PromiseFutureTest, WaitForValue) {
    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        promise.set_value(42);
    });

    EXPECT_EQ(future.wait_for(std::chrono::milliseconds(200)),
              std::future_status::ready);
    EXPECT_EQ(future.get(), 42);
    t.join();
}

TEST_F(PromiseFutureTest, WaitForTimeout) {
    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        promise.set_value(42);
    });

    EXPECT_EQ(future.wait_for(std::chrono::milliseconds(100)),
              std::future_status::timeout);
    t.join();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
