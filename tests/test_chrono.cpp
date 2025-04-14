#include <chrono>
#include <gtest/gtest.h>
#include <thread>

class ChronoTest : public ::testing::Test {
  protected:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;

    void SetUp() override { start = std::chrono::steady_clock::now(); }

    void TearDown() override {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl;
    }
};

class ChronoConvert {
  public:
    static double SecToMs(double sec) { return sec * 1000; }
    static double MsToSec(double ms) { return ms / 1000; }
    static double SecToUs(double sec) { return sec * 1000000; }
    static double UsToSec(double us) { return us / 1000000; }
    static double MsToUs(double ms) { return ms * 1000; }
    static double UsToMs(double us) { return us / 1000; }
};

TEST_F(ChronoTest, SleepFor100ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

TEST(ChronoConvertTest, Conversion) {
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToMs(1.0), 1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToSec(1000.0), 1.0);
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToUs(1.0), 1000000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToSec(1000000.0), 1.0);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToUs(1.0), 1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToMs(1000.0), 1.0);
}

TEST(ChronoConvertTest, DurationCast) {
    std::chrono::seconds s(1);
    std::chrono::milliseconds ms(1000);
    std::chrono::microseconds us(1000000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(s).count(),
              1000);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::seconds>(ms).count(), 1);
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::microseconds>(us).count(),
              1000000);
}

TEST(ChronoConvertTest, BoundaryConditions) {
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToMs(0), 0);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToSec(0), 0);
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToUs(0), 0);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToSec(0), 0);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToUs(0), 0);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToMs(0), 0);

    EXPECT_DOUBLE_EQ(ChronoConvert::SecToMs(-1), -1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToSec(-1000), -1);
    EXPECT_DOUBLE_EQ(ChronoConvert::SecToUs(-1), -1000000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToSec(-1000000), -1);
    EXPECT_DOUBLE_EQ(ChronoConvert::MsToUs(-1), -1000);
    EXPECT_DOUBLE_EQ(ChronoConvert::UsToMs(-1000), -1);
}

TEST(ChronoConvertTest, PerformanceTest) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        ChronoConvert::SecToMs(1.0);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Performance test duration: " << duration.count() << " ms"
              << std::endl;
}

TEST(ChronoConvertTest, InvalidArgument) {
    EXPECT_NO_THROW(
        ChronoConvert::SecToMs(std::numeric_limits<double>::infinity()));
    EXPECT_NO_THROW(
        ChronoConvert::MsToSec(std::numeric_limits<double>::infinity()));
    EXPECT_NO_THROW(
        ChronoConvert::SecToUs(std::numeric_limits<double>::infinity()));
    EXPECT_NO_THROW(
        ChronoConvert::UsToSec(std::numeric_limits<double>::infinity()));
    EXPECT_NO_THROW(
        ChronoConvert::MsToUs(std::numeric_limits<double>::infinity()));
    EXPECT_NO_THROW(
        ChronoConvert::UsToMs(std::numeric_limits<double>::infinity()));
}

/*
 *
 * gtest 入口 
 * */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
