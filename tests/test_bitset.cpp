#include <bitset>
#include <gtest/gtest.h>

// 测试 bitset 的基本构造和大小
TEST(BitsetTest, ConstructionAndSize) {
    std::bitset<8> b1; // 默认构造，所有位为0
    EXPECT_EQ(b1.size(), 8);
    EXPECT_EQ(b1.count(), 0);
    EXPECT_EQ(b1.any(), false);
    EXPECT_EQ(b1.none(), true);

    std::bitset<8> b2(0b10101010);
    EXPECT_EQ(b2.count(), 4);
    EXPECT_EQ(b2[1], true);
    EXPECT_EQ(b2[0], false);

    std::bitset<8> b3(std::string("1100"));
    EXPECT_EQ(b3[0], false);
    EXPECT_EQ(b3[1], false);
    EXPECT_EQ(b3[2], true);
    EXPECT_EQ(b3[3], true);
}

// 测试 bitset 的 set/reset/flip 操作
TEST(BitsetTest, SetResetFlip) {
    std::bitset<4> b;
    b.set();
    EXPECT_EQ(b.to_ulong(), 0b1111);

    b.reset(1);
    EXPECT_EQ(b.to_ulong(), 0b1101);

    b.flip(0);
    EXPECT_EQ(b.to_ulong(), 0b1100);

    b.reset();
    EXPECT_EQ(b.to_ulong(), 0);
}

// 测试 bitset 的 to_string 和 to_ulong
TEST(BitsetTest, ToStringAndToUlong) {
    std::bitset<4> b(0b1011);
    EXPECT_EQ(b.to_string(), "1011");
    EXPECT_EQ(b.to_ulong(), 11);
}

// 测试 bitset 的逻辑运算
TEST(BitsetTest, BitwiseOperations) {
    std::bitset<4> a(0b1100);
    std::bitset<4> b(0b1010);

    auto c = a & b;
    EXPECT_EQ(c.to_ulong(), 0b1000);

    c = a | b;
    EXPECT_EQ(c.to_ulong(), 0b1110);

    c = a ^ b;
    EXPECT_EQ(c.to_ulong(), 0b0110);

    c = ~a;
    EXPECT_EQ(c.to_ulong(), 0b0011);
}

// 测试 bitset 的下标操作
TEST(BitsetTest, IndexOperator) {
    std::bitset<8> b;
    b[3] = 1;
    b[4] = true;
    EXPECT_EQ(b[3], true);
    EXPECT_EQ(b[4], true);
    EXPECT_EQ(b.count(), 2);
}

// 权限控制
enum Permission { READ = 0, WRITE = 1, EXECUTE = 2 };

TEST(BitsetTest, Permission) {
    std::bitset<3> p;
    p.set(Permission::READ);
    p.set(Permission::EXECUTE);
    EXPECT_EQ(p.test(Permission::READ), true);
    EXPECT_EQ(p.test(Permission::WRITE), false);
    EXPECT_EQ(p.test(Permission::EXECUTE), true);
}

// 状态控制
enum State { INIT = 0, READY = 1, RUNNING = 2, FINISH = 3 };

TEST(BitsetTest, State) {
    std::bitset<4> s;
    s.set(0);
    s.set(1);
    EXPECT_EQ(s.test(State::INIT), true);
    EXPECT_EQ(s.test(State::READY), true);
    EXPECT_EQ(s.test(State::RUNNING), false);
    EXPECT_EQ(s.test(State::FINISH), false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
