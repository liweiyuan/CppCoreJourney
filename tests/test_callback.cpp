#include <functional>
#include <gtest/gtest.h>
#include <vector>

class CallbackTest : public ::testing::Test {
protected:
  std::vector<std::function<void(int)>> callbacks;

  void SetUp() override {
    callbacks.push_back(
        [](int x) { std::cout << "Callback 1: " << x << std::endl; });
    callbacks.push_back(
        [](int x) { std::cout << "Callback 2: " << x << std::endl; });
  }

  void TearDown() override { callbacks.clear(); }
};

TEST_F(CallbackTest, AddCallback) { EXPECT_EQ(callbacks.size(), 2); }

TEST_F(CallbackTest, ExecuteCallbacks) {
  for (auto &callback : callbacks) {
    callback(42);
  }
}

TEST_F(CallbackTest, ClearCallbacks) {
  callbacks.clear();
  EXPECT_TRUE(callbacks.empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
