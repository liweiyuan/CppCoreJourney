// 学习使用结构化绑定
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

// 数组结构化绑定
TEST(BindTest, Array) {
    int a[2] = {1, 2};
    auto [x, y] = a;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
}

// std::pair结构化绑定
TEST(BindTest, Pair) {
    std::pair<int, std::string> p = {42, "Hello"};
    auto [a, b] = p;
    EXPECT_EQ(a, 42);
    EXPECT_EQ(b, "Hello");
}
// std::tuple结构化绑定
TEST(BindTest, Tuple) {
    std::tuple<int, std::string, double> t = {42, "Hello", 3.14};
    auto [a, b, c] = t;
    EXPECT_EQ(a, 42);
    EXPECT_EQ(b, "Hello");
    EXPECT_DOUBLE_EQ(c, 3.14);
}

// std::map结构化绑定
TEST(BindTest, Map) {
    std::map<std::string, int> m = {{"one", 1}, {"two", 2}};
    for (const auto &[key, value] : m) {
        std::cout << key << ": " << value << std::endl;
    }
}
// std::vector结构化绑定
TEST(BindTest, Vector) {
    std::vector<std::pair<int, std::string>> v = {{1, "one"}, {2, "two"}};
    for (const auto &[a, b] : v) {
        std::cout << a << ": " << b << std::endl;
    }
}

// std::array结构化绑定
TEST(BindTest, Array1) {
    std::array<int, 2> a = {1, 2};
    auto [x, y] = a;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
}

// 自定义结构体结构化绑定
struct Point {
    int x, y;
};
TEST(BindTest, Struct) {
    Point p = {1, 2};
    auto [a, b] = p;
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
}
// 自定义复杂的结构体结构化绑定
struct Person {
    std::string name;
    int age;
    std::vector<std::string> hobbies;
};
TEST(BindTest, ComplexStruct) {
    Person p = {"Alice", 30, {"reading", "swimming"}};
    auto [name, age, hobbies] = p;
    EXPECT_EQ(name, "Alice");
}

// class结构化绑定
class MyClass {
  public:
    MyClass(int a, int b) : a(a), b(b) {}
    int getA() const { return a; }
    int getB() const { return b; }

    int a, b;
};

TEST(BindTest, Class) {
    MyClass obj(1, 2);
    auto [x, y] = obj;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}