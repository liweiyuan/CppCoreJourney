#include <algorithm>
#include <functional>
#include <gtest/gtest.h>

struct IsEven {
    bool operator()(int x) const { return x % 2 == 0; }
};

TEST(FunctionTest, IsEven) {
    EXPECT_TRUE(IsEven()(2));
    EXPECT_FALSE(IsEven()(3));
}

// 测试一个vector
TEST(FunctionTest, Vector) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v2), IsEven());
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 4);
    EXPECT_EQ(v2[2], 6);
    EXPECT_EQ(v2[3], 8);
    EXPECT_EQ(v2[4], 10);
}

// 测试标准库中的函数对象
TEST(FunctionTest, StandardFunctionObject) {
    std::plus<int> addr;
    EXPECT_EQ(addr(1, 2), 3);
    std::multiplies<int> mul;
    EXPECT_EQ(mul(2, 3), 6);
    std::minus<int> sub;
    EXPECT_EQ(sub(3, 2), 1);
    std::divides<int> div;
    EXPECT_EQ(div(3, 2), 1);
    std::modulus<int> mod;
    EXPECT_EQ(mod(3, 2), 1);
    std::equal_to<int> equal;
    EXPECT_TRUE(equal(3, 3));
    std::not_equal_to<int> not_equal;
    EXPECT_TRUE(not_equal(3, 4));
    std::less<int> less;
    EXPECT_TRUE(less(3, 4));
    std::greater<int> greater;
    EXPECT_TRUE(greater(4, 3));
    std::less_equal<int> less_equal;
    EXPECT_TRUE(less_equal(3, 3));
    std::greater_equal<int> greater_equal;
    EXPECT_TRUE(greater_equal(3, 3));
}

// 测试使用lambda来代替函数对象
TEST(FunctionTest, Lambda) {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2;
    std::copy_if(v.begin(), v.end(), std::back_inserter(v2),
                 [](int x) { return x % 2 == 0; });
    EXPECT_EQ(v2.size(), 5);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 4);
    EXPECT_EQ(v2[2], 6);
    EXPECT_EQ(v2[3], 8);
    EXPECT_EQ(v2[4], 10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}