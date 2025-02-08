
#include "state.hpp"
#include <gtest/gtest.h>
#include <string>
#include <variant>

struct Visitor {
  std::variant<int, float, std::string> operator()(int i) const { return i; }
  std::variant<int, float, std::string> operator()(float f) const { return f; }
  std::variant<int, float, std::string> operator()(const std::string &s) const {
    return s;
  }
};

TEST(TestVariants, test_type) {
  std::variant<int, float, std::string> v = 3.14f;
  auto result = std::visit(Visitor{}, v);

  EXPECT_TRUE(std::holds_alternative<float>(result));
  std::visit(
      [](auto &&value) {
        if constexpr (std::is_same_v<std::decay_t<decltype(value)>, float>) {
          EXPECT_FLOAT_EQ(value, 3.14f);
        } else {
          FAIL() << "Unexpected type in variant!";
        }
      },
      result);
}

TEST(TestVariants, test_type_string) {
  std::variant<int, float, std::string> v = "Hello, World!";
  auto result = std::visit(Visitor{}, v);

  std::string expected = "Hello, World!";
  std::string actual = std::get<std::string>(result);
  EXPECT_EQ(expected, actual);

  // 更推荐的方式
  auto value = std::get_if<std::string>(&result);
  if (value) {
    EXPECT_EQ(*value, expected);
  }
}

// 单元测试代码
TEST(FSMTest, TestStateTransitions) {
  FSM fsm;

  // 初始状态应为 Idle
  EXPECT_TRUE(std::holds_alternative<Idle>(fsm.getCurrentState()));

  // 发送 Start 事件，状态应转换为 Processing
  fsm.handleEvent(Event::Start);
  EXPECT_TRUE(std::holds_alternative<Processing>(fsm.getCurrentState()));

  // 发送 Complete 事件，状态应转换为 Completed
  fsm.handleEvent(Event::Complete);
  EXPECT_TRUE(std::holds_alternative<Completed>(fsm.getCurrentState()));

  // 发送 Reset 事件，状态应转换回 Idle
  fsm.handleEvent(Event::Reset);
  EXPECT_TRUE(std::holds_alternative<Idle>(fsm.getCurrentState()));
}

TEST(FSMTest, TestResetEventFromProcessing) {
  FSM fsm;

  // 发送 Start 事件，状态应转换为 Processing
  fsm.handleEvent(Event::Start);
  EXPECT_TRUE(std::holds_alternative<Processing>(fsm.getCurrentState()));

  // 发送 Reset 事件，状态应转换回 Idle
  fsm.handleEvent(Event::Reset);
  EXPECT_TRUE(std::holds_alternative<Idle>(fsm.getCurrentState()));
}

int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}