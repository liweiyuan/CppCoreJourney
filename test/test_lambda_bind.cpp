#include <gtest/gtest.h>

int add(int a, int b) { return a + b; }

TEST(BindTests, test_bind) {
  auto bound_add = std::bind(add, 10, std::placeholders::_1);
  EXPECT_EQ(bound_add(5), 15);
  EXPECT_EQ(bound_add(100), 110);
}

TEST(BindTests, test_placeholder) {
  auto bound_add = std::bind(add, 10, 5);
  EXPECT_EQ(bound_add(), 15);
}

// 同样的功能使用lambda来实现
TEST(LambdaTests, test_lambda) {
  auto sum = [](int a, int b) { return a + b; };
  EXPECT_EQ(3, sum(1, 2));
  EXPECT_EQ(10, sum(5, 5));
}

int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}