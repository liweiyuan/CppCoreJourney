#include <gtest/gtest.h>
#include <optional>
#include <string>

class OptionalTest : public ::testing::Test {
  protected:
    std::optional<int> optInt;
    std::optional<std::string> optString;

    void SetUp() override {
        optInt = 42;
        optString = "Hello";
    }
};

TEST_F(OptionalTest, HasValue) {
    EXPECT_TRUE(optInt.has_value());
    EXPECT_TRUE(optString.has_value());
}

TEST_F(OptionalTest, Value) {
    EXPECT_EQ(optInt.value(), 42);
    EXPECT_EQ(optString.value(), "Hello");
}

TEST_F(OptionalTest, Reset) {
    optInt.reset();
    optString.reset();
    EXPECT_FALSE(optInt.has_value());
    EXPECT_FALSE(optString.has_value());
}

TEST_F(OptionalTest, Emplace) {
    optInt.emplace(100);
    optString.emplace("World");
    EXPECT_EQ(optInt.value(), 100);
    EXPECT_EQ(optString.value(), "World");
}

TEST_F(OptionalTest, ValueOr) {
    optInt.reset();
    optString.reset();
    EXPECT_EQ(optInt.value_or(10), 10);
    EXPECT_EQ(optString.value_or("Default"), "Default");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
