
#include <algorithm>
#include <gtest/gtest.h>
#include <optional>
#include <vector>

std::optional<int> getValue(bool condition) {
  if (condition) {
    return 42;
  }
  return std::nullopt;
}

TEST(OptionalTests, test_optional_value) {
  auto value = getValue(true);
  EXPECT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), 42);

  value = getValue(false);
  EXPECT_FALSE(value.has_value());
  EXPECT_THROW(value.value(), std::bad_optional_access);
}

std::optional<int> find(const std::vector<int> &numbers, int threshold) {
  auto it = std::find_if(numbers.begin(), numbers.end(),
                         [threshold](int num) { return num > threshold; });
  if (it != numbers.end()) {

    return *it;
  }
  return std::nullopt;
}

TEST(OptionalTests, test_optional_find) {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  auto value = find(numbers, 3);
  EXPECT_TRUE(value.has_value());
  EXPECT_EQ(value.value(), 4);

  value = find(numbers, 10);
  EXPECT_FALSE(value.has_value());
  EXPECT_THROW(value.value(), std::bad_optional_access);
}

std::vector<int> findAllGreater(const std::vector<int> &numbers,
                                int threshold) {
  std::vector<int> result;
  std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(result),
               [threshold](int num) { return num > threshold; });
  return result;
}

TEST(OptionalTests, test_optional_find_all) {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  auto values = findAllGreater(numbers, 3);
  EXPECT_EQ(values.size(), 2);
  EXPECT_TRUE(std::find(values.begin(), values.end(), 4) != values.end());
}

int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}