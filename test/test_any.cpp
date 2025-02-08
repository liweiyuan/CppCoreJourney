#include <any>
#include <gtest/gtest.h>
#include <string>

TEST(AnyTests, test_any_number) {
  std::any number = 10;
  EXPECT_EQ(std::any_cast<int>(number), 10);
}

TEST(AnyTests, test_any_string) {
  std::any string = std::string("Hello, World!");
  EXPECT_EQ(std::any_cast<std::string>(string), "Hello, World!");
}

TEST(AnyTests, test_any_type) {
  std::any any_type = 10;
  EXPECT_TRUE(any_type.type() == typeid(int));
}

TEST(AnyTests, test_any_copy) {
  std::any str = std::string("hello");
  std::any copied_str = str;
  EXPECT_EQ(std::any_cast<std::string>(str),
            std::any_cast<std::string>(copied_str));
}

/**
移动原始的数据
 */
TEST(AnyTests, test_any_move) {
  std::any str = std::string("hello");
  std::any moved_str = std::move(str);
  // 检查原先的std::any是否为空
  EXPECT_FALSE(str.has_value());
  EXPECT_EQ(std::any_cast<std::string>(moved_str), "hello");
}

int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}