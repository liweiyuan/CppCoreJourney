#include <gtest/gtest.h>
#include <memory>
#include <vector>

class AllocatorTest : public ::testing::Test {
  protected:
    std::allocator<int> allocator;
    int *p;

    void SetUp() override { p = allocator.allocate(1); }

    void TearDown() override { allocator.deallocate(p, 1); }
};

TEST_F(AllocatorTest, AllocateAndDeallocate) { EXPECT_NE(p, nullptr); }

TEST_F(AllocatorTest, ConstructAndDestroy) {
    allocator.construct(p, 42);
    EXPECT_EQ(*p, 42);
    allocator.destroy(p);
}

TEST_F(AllocatorTest, VectorWithCustomAllocator) {
    std::vector<int, std::allocator<int>> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
