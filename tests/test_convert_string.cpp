#include "convert_string.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <optional>
#include <string>
TEST(ConvertStringTest, ConvertToInt) {
    ConvertString cs("123");
    EXPECT_EQ(cs.to<int>(), 123);
}

TEST(ConvertStringTest, ConvertToFloat) {
    ConvertString cs("123.3");
    auto result = cs.to<float>();
    if (result.has_value()) {
        EXPECT_EQ(result.value(), 123.3f);
    }
}

TEST(ConvertStringTest, ConvertToDouble) {
    ConvertString cs("123.3");
    EXPECT_EQ(cs.to<double>(), 123.3);
}

TEST(ConvertStringTest, ConvertToNullopt) {
    ConvertString cs("sss");
    EXPECT_EQ(cs.to<double>(), std::nullopt);
}

TEST(ConvertStringTest, ConvertToString) {
    ConvertString cs("sss");
    EXPECT_EQ(cs.to<std::string>(), "sss");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}