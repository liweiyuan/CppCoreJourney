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

// 新增布尔类型测试
TEST(ConvertStringTest, ConvertToBool) {
    // 测试真值
    EXPECT_EQ(ConvertString("true").to<bool>(), true);
    EXPECT_EQ(ConvertString("1").to<bool>(), true);
    EXPECT_EQ(ConvertString("2").to<bool>(), true);

    // 测试假值
    EXPECT_EQ(ConvertString("false").to<bool>(), false);
    EXPECT_EQ(ConvertString("0").to<bool>(), false);

    // 测试无效值
    EXPECT_EQ(ConvertString("ture").to<bool>(), std::nullopt);

    // 测试大小写不敏感
    EXPECT_EQ(ConvertString("True").to<bool>(), true);
    EXPECT_EQ(ConvertString("FALSE").to<bool>(), false);
}

// 增强字符串测试
TEST(ConvertStringTest, ConvertToString) {
    // 测试包含空格的字符串
    EXPECT_EQ(ConvertString("hello world").to<std::string>(), "hello world");
    // 测试空字符串
    EXPECT_EQ(ConvertString("").to<std::string>(), "");
}

// 新增边界值测试
TEST(ConvertStringTest, BoundaryValues) {
    // 最大整型值测试
    EXPECT_EQ(ConvertString("2147483647").to<int>(), 2147483647);
    // 浮点精度极限测试
    EXPECT_NEAR(ConvertString("3.4028235e38").to<float>().value(),
                3.4028235e38f, 1e32f);
}

// 增强无效输入测试
TEST(ConvertStringTest, InvalidInputs) {
    // 部分有效数字
    EXPECT_EQ(ConvertString("123abc").to<int>(), std::nullopt);
    // 非法浮点数
    EXPECT_EQ(ConvertString("12.34.56").to<double>(), std::nullopt);
    // 溢出测试
    EXPECT_EQ(ConvertString("99999999999999999999").to<int>(), std::nullopt);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}