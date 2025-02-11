// 测试skiplist.hpp实现的跳表
#include "skiplist.hpp"
#include <gtest/gtest.h>

TEST(SkipListTests, test_skip_list) {
    srand(time(0)); // 初始化随机数种子
    SkipList<int> skip_list;
    skip_list.insert(1);
    skip_list.insert(2);
    skip_list.insert(3);
    skip_list.insert(4);
    skip_list.insert(5);
    skip_list.insert(6);
    skip_list.insert(7);
    skip_list.insert(8);
    skip_list.insert(9);
    skip_list.insert(10);
    EXPECT_TRUE(skip_list.search(1));
    EXPECT_TRUE(skip_list.search(2));
    EXPECT_TRUE(skip_list.search(3));
    EXPECT_TRUE(skip_list.search(4));
    EXPECT_TRUE(skip_list.search(5));
    EXPECT_TRUE(skip_list.search(6));
    EXPECT_TRUE(skip_list.search(7));
    EXPECT_TRUE(skip_list.search(8));
    EXPECT_TRUE(skip_list.search(9));
    EXPECT_TRUE(skip_list.search(10));
    EXPECT_FALSE(skip_list.search(11));
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
