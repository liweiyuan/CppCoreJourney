#include <gtest/gtest.h>
#include <string>
#include <variant>

class VariantTest : public ::testing::Test {
  protected:
    std::variant<int, std::string> variant;

    void SetUp() override { variant = 42; }
};

TEST_F(VariantTest, HoldsAlternative) {
    EXPECT_TRUE(std::holds_alternative<int>(variant));
    EXPECT_FALSE(std::holds_alternative<std::string>(variant));
}

TEST_F(VariantTest, GetValue) {
    EXPECT_EQ(std::get<int>(variant), 42);
    variant = "Hello";
    EXPECT_EQ(std::get<std::string>(variant), "Hello");
}

TEST_F(VariantTest, GetIf) {
    EXPECT_NE(std::get_if<int>(&variant), nullptr);
    EXPECT_EQ(std::get_if<std::string>(&variant), nullptr);
    variant = "Hello";
    EXPECT_EQ(std::get_if<int>(&variant), nullptr);
    EXPECT_NE(std::get_if<std::string>(&variant), nullptr);
}

TEST_F(VariantTest, Visit) {
    variant = "Hello";
    std::visit(
        [](auto &&arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                EXPECT_EQ(arg, 42);
            } else if constexpr (std::is_same_v<T, std::string>) {
                EXPECT_EQ(arg, "Hello");
            }
        },
        variant);
}

TEST_F(VariantTest, BadVariantAccess) {
    EXPECT_THROW(std::get<std::string>(variant), std::bad_variant_access);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
