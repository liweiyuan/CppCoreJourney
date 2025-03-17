#include <gtest/gtest.h>
#include <string>
#include <tuple>

class TupleTest : public ::testing::Test {
  protected:
    std::tuple<int, std::string, double> tuple;

    void SetUp() override { tuple = std::make_tuple(42, "Hello", 3.14); }
};

TEST_F(TupleTest, GetValues) {
    EXPECT_EQ(std::get<0>(tuple), 42);
    EXPECT_EQ(std::get<1>(tuple), "Hello");
    EXPECT_DOUBLE_EQ(std::get<2>(tuple), 3.14);
}

TEST_F(TupleTest, SetValues) {
    std::get<0>(tuple) = 100;
    std::get<1>(tuple) = "World";
    std::get<2>(tuple) = 2.71;

    EXPECT_EQ(std::get<0>(tuple), 100);
    EXPECT_EQ(std::get<1>(tuple), "World");
    EXPECT_DOUBLE_EQ(std::get<2>(tuple), 2.71);
}

TEST_F(TupleTest, TupleSize) {
    EXPECT_EQ(std::tuple_size<decltype(tuple)>::value, 3);
}

TEST_F(TupleTest, TupleElement) {
    EXPECT_TRUE((std::is_same<std::tuple_element<0, decltype(tuple)>::type,
                              int>::value));
    EXPECT_TRUE((std::is_same<std::tuple_element<1, decltype(tuple)>::type,
                              std::string>::value));
    EXPECT_TRUE((std::is_same<std::tuple_element<2, decltype(tuple)>::type,
                              double>::value));
}

TEST_F(TupleTest, test_tie) {
    int a;
    std::string b;
    double c;
    std::tie(a, b, c) = tuple;
    EXPECT_EQ(a, 42);
    EXPECT_EQ(b, "Hello");
    EXPECT_DOUBLE_EQ(c, 3.14);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
