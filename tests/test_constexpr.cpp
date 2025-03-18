#include <gtest/gtest.h>

TEST(ConstexprTests, test_basic) {
    constexpr double radius{3.0};
    constexpr double pi{3.14159};
    constexpr double circumference{2 * pi * radius};
    EXPECT_DOUBLE_EQ(circumference, 18.84954);
}

constexpr double square(double x) { return x * x; }

TEST(ConstexprTests, test_square) {
    constexpr double side{4.0};
    constexpr double area{square(side)};
    EXPECT_DOUBLE_EQ(area, 16.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}