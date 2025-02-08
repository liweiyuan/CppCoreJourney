#include <cstdlib>
#include <gtest/gtest.h>
template <typename T> struct ExtAllocator {
    using value_type = T;

    ExtAllocator() = default;

    template <typename U> ExtAllocator(const ExtAllocator<U> &) {}

    // 分配内存
    T *allocate(std::size_t n) {
        if (n == 0) {
            return nullptr;
        }
        void *p = std::malloc(n * sizeof(T));
        if (!p) {
            throw std::bad_alloc();
        }
        std::cout << "Allocating " << n << " elements, " << n * sizeof(T)
                  << " bytes." << std::endl;
        return static_cast<T *>(p);
    }

    void deallocate(T *ptr, std::size_t n) {
        if (ptr) {
            std::cout << "Deallocating " << n << " elements, " << n * sizeof(T)
                      << " bytes." << std::endl;
            std::free(ptr);
        }
    }

    // 构造对象
    void construct(T *ptr, const T &value) { new (ptr) T(value); }

    // 销毁对象
    void destroy(T *ptr) { ptr->~T(); }

    template <typename U> struct rebind {
        using other = ExtAllocator<U>;
    };

    // 显式实现 operator== 和 operator!=，以满足 std::vector 需要比较 Allocator
    // 的要求
    bool operator==(const ExtAllocator &other) const {
        return true; // 简单示例，假设所有 MyAllocator 都相等
    }

    bool operator!=(const ExtAllocator &other) const {
        return !(*this == other);
    }
};

TEST(AlloctorTests, test_vector_insert) {
    // ExtAllocator<int> alloc;
    std::vector<int, ExtAllocator<int>> vec;

    // 插入元素
    vec.insert(vec.end(), 10);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 10);
}

// 测试vector扩容机制
TEST(AlloctorTests, test_vector_resize) {
    // ExtAllocator<int> alloc;
    std::vector<int, ExtAllocator<int>> vec;

    // 扩容到 10 元素
    vec.resize(10);
    EXPECT_EQ(vec.size(), 10);
    EXPECT_TRUE(vec.capacity() >= 10);

    // 再次 resize 到 5 元素
    vec.resize(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_TRUE(vec.capacity() >= 5);

    // 清空元素
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.capacity() >= 10); // 容量不变，保证 resize 后不再申请新内存

    // 释放内存
    vec.resize(20);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 20);
    EXPECT_FALSE(vec.capacity() == 0); // 容量为 0，释放了所有内存
    vec.resize(1);
    vec.shrink_to_fit();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_FALSE(vec.capacity() == 0); // 容量为 0，释放了所有内存
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}