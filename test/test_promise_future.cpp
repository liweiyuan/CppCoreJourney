
#include <future>
#include <gtest/gtest.h>
#include <thread>

void producer(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    p.set_value(42);
    std::cout << "Value set by producer.\n";
}

void consumer(std::future<int> f) {
    std::cout << "Consumer waiting for value...\n";
    int value = f.get(); // 获取值，可能会阻塞
    std::cout << "Value received by consumer: " << value << "\n";
}

TEST(PromiseFutureTests, test_promise_future) {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread producerThread(producer, std::move(p));
    std::thread consumerThread(consumer, std::move(f));

    producerThread.join();
    consumerThread.join();
}

// 通过std::promise在异步线程之间，传递线程
void producerAsync(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    p.set_value(42);
    std::cout << "Value set by producerAsync.\n";
}

void consumerAsync(std::future<int> f) {
    std::cout << "Consumer waiting for value...\n";
    int value = f.get(); // 获取值，可能会阻塞
    std::cout << "Value received by consumerAsync: " << value << "\n";
}

TEST(PromiseFutureTests, test_promise_future_async) {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread producerThread([&]() { producerAsync(std::move(p)); });
    std::thread consumerThread([&]() { consumerAsync(std::move(f)); });

    producerThread.join();
    consumerThread.join();
}

// 通过std::promise在设置异常
void producerException(std::promise<int> p) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    p.set_exception(std::make_exception_ptr(std::runtime_error("Error")));
    std::cout << "Exception set by producerException.\n";
}

void consumerException(std::future<int> f) {
    std::cout << "Consumer waiting for value...\n";
    try {
        int value = f.get(); // 获取值，可能会阻塞
        std::cout << "Value received by consumerException: " << value << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << "\n";
    }
    std::cout << "Consumer finished.\n";
}

TEST(PromiseFutureTests, test_promise_future_exception) {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread producerThread(producerException, std::move(p));
    std::thread consumerThread(consumerException, std::move(f));

    producerThread.join();
    consumerThread.join();
}
int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}