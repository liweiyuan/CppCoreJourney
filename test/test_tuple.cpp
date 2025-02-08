#include <gtest/gtest.h>
#include <string>
#include <tuple>

std::tuple<int, double, std::string> getValues() {
  return std::make_tuple(10, 3.14, "Hello, World!");
}

TEST(TestTuples, test_getValues) {
  auto t = getValues();
  EXPECT_EQ(std::get<0>(t), 10);
  EXPECT_EQ(std::get<1>(t), 3.14);
  EXPECT_EQ(std::get<2>(t), "Hello, World!");
}

TEST(TestTuples, test_bind) {

  std::tuple<int, double, std::string> t(10, 3.14, "Hello, World!");

  auto [a, b, c] = t;
  EXPECT_EQ(a, 10);
  EXPECT_EQ(b, 3.14);
  EXPECT_EQ(c, "Hello, World!");
}

TEST(TestTuples, test_get) {
  auto t = getValues();
  EXPECT_EQ(std::get<0>(t), 10);
  EXPECT_EQ(std::get<1>(t), 3.14);
  EXPECT_EQ(std::get<2>(t), "Hello, World!");
}

void print(int a, double b, const std::string &c) {
  std::cout << "a: " << a << ", b: " << b << ", c: " << c << std::endl;
}

TEST(TestTuples, test_apply) {
  auto t = getValues();
  std::apply(print, t);

  std::tuple<int, double, std::string> tuple(1, 2.0, "hello");
  std::apply(print, tuple);
}
int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}