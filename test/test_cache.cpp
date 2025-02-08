#include "safe_cache.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(SafeLRUCacheTests, test_safe_lru_cache) {
    SafeLRUCache<int, std::string> cache(2);
    cache.put(1, "one");                    // 移动语义
    cache.put(2, "two");                    // 移动语义
    EXPECT_EQ(cache.get(1).value(), "one"); // 移动语义
    cache.put(3, "three");
    EXPECT_FALSE(cache.get(2).has_value());
    EXPECT_EQ(cache.get(1).value(), "one");
    EXPECT_EQ(cache.get(3).value(), "three");

    std::string value("four"); // 拷贝语义
    cache.put(4, value);
    EXPECT_TRUE(cache.get(3).has_value());
    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.get(3).value(), "three");
    EXPECT_EQ(cache.get(4).value(), "four");
}

TEST(SafeLRUCacheTests, test_safe_lru_cache_boundary) {
    // 使用 try catch 测试边界条件
    try {
        SafeLRUCache<int, std::string> cache(0);
        cache.put(1, "one");
        cache.put(2, "two");
    } catch (const std::exception &e) {
        // 捕获异常，测试通过
        EXPECT_STREQ(e.what(), "Capacity must be positive");
        EXPECT_TRUE(true);
    }
}

TEST(SafeLRUCacheTests, test_safe_lru_cache_negative) {
    // 使用 try catch 测试边界条件
    try {
        SafeLRUCache<int, std::string> cache(-1);
        cache.put(1, "one");
        cache.put(2, "two");
    } catch (const std::exception &e) {
        // 校验异常类型
        EXPECT_STREQ(e.what(), "Capacity must be positive");
        EXPECT_TRUE(true);
    }
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
