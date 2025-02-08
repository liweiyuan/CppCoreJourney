#include "callback.hpp"
#include <gtest/gtest.h>
#include <memory>

// 测试类定义
TEST(CallbackTest, called) {
    auto callback = std::make_shared<CallbackClass>();
    callback->set_callback();
    std::string result = callback->call_callback();
    EXPECT_EQ("Callback function called", result);
}

TEST(CallbackTest, empty) {
    auto callback = std::make_shared<CallbackClass>();
    // callback.set_callback();
    std::string result = callback->call_callback();
    EXPECT_EQ("Callback function not set", result);
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
