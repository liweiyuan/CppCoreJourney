#include "safe_cache.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(SafeLRUCacheTests, test_safe_lru_cache) {
    SafeLRUCache<int, std::string> cache(2);
    cache.put(1, "one"); //移动语义
    cache.put(2, "two"); //移动语义
    EXPECT_EQ(cache.get(1).value(), "one"); //移动语义
    cache.put(3, "three");
    EXPECT_FALSE(cache.get(2).has_value());
    EXPECT_EQ(cache.get(1).value(), "one");
    EXPECT_EQ(cache.get(3).value(), "three");

    std::string value("four"); //拷贝语义
    cache.put(4, value);
    EXPECT_TRUE(cache.get(3).has_value());
    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.get(3).value(), "three");
    EXPECT_EQ(cache.get(4).value(), "four");
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
