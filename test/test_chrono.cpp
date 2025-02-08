#include <chrono>
#include <gtest/gtest.h>
#include <thread>

TEST(TestsChrono, test_chrono) {
    std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::chrono::steady_clock::time_point end =
        std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;
}

class ChronoConvert {
  public:
    static double SecToMs(double sec) { return sec * 1000; }

    static double MsToSec(double ms) { return ms / 1000; }

    static double SecToUs(double sec) { return sec * 1000000; }

    static double UsToSec(double us) { return us / 1000000; }

    static double MsToUs(double ms) { return ms * 1000; }

    static double UsToMs(double us) { return us / 1000; }
};

TEST(TestsChrono, test_chrono_convert) {
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToMs(1.0), 1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToSec(1000.0), 1.0);
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToUs(1.0), 1000000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToSec(1000000.0), 1.0);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToUs(1.0), 1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToMs(1000.0), 1.0);

    // 使用 std::chrono::duration_cast来转换
    std::chrono::seconds s(1);
    std::chrono::milliseconds ms(1000);
    std::chrono::microseconds us(1000000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(s).count(),
              1000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(ms).count(), 1);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::microseconds>(us).count(),
              1000000);
}

TEST(TestsChrono, test_chrono2) {
    std::chrono::seconds s(1);
    std::chrono::milliseconds ms(1000);
    std::chrono::microseconds us(1000000);
    EXPECT_EQ(s.count(), 1);
    EXPECT_EQ(ms.count(), 1000);
    EXPECT_EQ(us.count(), 1000000);
}

// 使用std::chrono::high_resolution_clock来衡量一个函数的耗时，需要调用多次
TEST(TestsChrono, test_chrono3) {
    auto func = []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    };
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    EXPECT_GE(duration.count(), 100);
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}