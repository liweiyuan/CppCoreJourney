#include "safe_cache.hpp"
#include <gtest/gtest.h>
#include <string>

class SafeLRUCacheTest : public ::testing::Test {
  protected:
    SafeLRUCache<int, std::string> cache{2};

    void SetUp() override {
        cache.put(1, "one");
        cache.put(2, "two");
    }

    void TearDown() override {
        // No clear method, so we don't need to do anything here
    }
};

TEST_F(SafeLRUCacheTest, InsertAndRetrieve) {
    EXPECT_EQ(cache.get(1).value(), "one");
    EXPECT_EQ(cache.get(2).value(), "two");
}

TEST_F(SafeLRUCacheTest, RetrieveNonExistent) {
    EXPECT_FALSE(cache.get(3).has_value());
}

TEST_F(SafeLRUCacheTest, UpdateValue) {
    cache.put(1, "uno");
    EXPECT_EQ(cache.get(1).value(), "uno");
}

TEST_F(SafeLRUCacheTest, RemoveValue) {
    cache.remove(1);
    EXPECT_FALSE(cache.get(1).has_value());
}

TEST(SafeLRUCacheTests, BoundaryConditions) {
    try {
        SafeLRUCache<int, std::string> cache(0);
        cache.put(1, "one");
        cache.put(2, "two");
    } catch (const std::exception &e) {
        EXPECT_STREQ(e.what(), "Capacity must be positive");
    }

    try {
        SafeLRUCache<int, std::string> cache(-1);
        cache.put(1, "one");
        cache.put(2, "two");
    } catch (const std::exception &e) {
        EXPECT_STREQ(e.what(), "Capacity must be positive");
    }
}

TEST(SafeLRUCacheTests, PerformanceTest) {
    SafeLRUCache<int, std::string> cache(1000);
    for (int i = 0; i < 1000; ++i) {
        cache.put(i, "value" + std::to_string(i));
    }
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(cache.get(i).value(), "value" + std::to_string(i));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
