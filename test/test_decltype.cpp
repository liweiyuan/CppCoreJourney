#include <gtest/gtest.h>
#include <string>
#include <vector>

struct TData {
  std::vector<std::string> names;
};

int t() { return 42; }

// 返回一个右值，是一个易失值
int getValue() { return 42; }

TEST(DecltypeTests, test_fun) {
  auto f = t;
  EXPECT_EQ(f(), 42);

  using Type = decltype(t());
  EXPECT_TRUE((std::is_same<Type, int>::value));

  int x = 42;
  using Int = decltype(x);
  EXPECT_TRUE((std::is_same<Int, int>::value));

  int &&y = getValue();
  // 这个值是一个临时值，已经销毁，所以是未定义的
  //  EXPECT_EQ(y, 42);
  // EXPECT_EQ(getValue(), 42);
  using IntRef = decltype(y);
  EXPECT_TRUE((std::is_same<IntRef, int &&>::value));
}

TEST(DecltypeTests, test_attr) {
  TData data;
  using Type = decltype(data.names);
  EXPECT_TRUE((std::is_same<Type, std::vector<std::string>>::value));
}
int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}