// 测试skiplist.hpp实现的跳表
#include "skiplist.hpp"
#include <gtest/gtest.h>

TEST(SkipListTests, test_skip_list) {
    srand(time(0)); // 初始化随机数种子
    SkipList<int> skiplist;
    skiplist.insert(3);
    skiplist.insert(6);
    skiplist.insert(9);
    skiplist.insert(2);
    skiplist.insert(5);
    skiplist.insert(8);

    EXPECT_TRUE(skiplist.search(3));
    EXPECT_TRUE(skiplist.search(6));
    EXPECT_TRUE(skiplist.search(9));
    EXPECT_TRUE(skiplist.search(2));
    EXPECT_TRUE(skiplist.search(5));
    EXPECT_TRUE(skiplist.search(8));
    EXPECT_FALSE(skiplist.search(1));
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
