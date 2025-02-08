#include "config.hpp"
#include <gtest/gtest.h>

TEST(TestConfigs, test_config) {
    Config config;
    // 设置不同类型的配置项
    config.set("server_port", 8080);
    config.set("hostname", std::string("localhost"));
    config.set("database_name", std::string("test_db"));
    // 获取并检查配置项
    EXPECT_EQ(config.get<int>("server_port"), 8080);
    EXPECT_EQ(config.get<std::string>("hostname"), "localhost");
    EXPECT_EQ(config.get<std::string>("database_name"), "test_db");
}

TEST(TestConfigs, test_config_boundary) {
    Config config;
    config.set("empty_string", std::string(""));
    EXPECT_EQ(config.get<std::string>("empty_string"), "");

    config.set("special_chars", std::string("!@#$%^&*()"));
    EXPECT_EQ(config.get<std::string>("special_chars"), "!@#$%^&*()");
}

TEST(TestConfigs, test_config_exception) {
    Config config;
    EXPECT_THROW(config.get<int>("non_existent_key"), std::out_of_range);
}
TEST(TestConfigs, SetAndGet) {
    Config config;

    config.set<int>("key1", 42);
    EXPECT_EQ(config.get<int>("key1"), 42);

    config.set<std::string>("key2", "Hello, World!");
    EXPECT_EQ(config.get<std::string>("key2"), "Hello, World!");
}

TEST(TestConfigs, InvalidKey) {
    Config config;

    EXPECT_THROW(config.get<int>("invalid_key"), std::out_of_range);
}

int main(int argc, char **argv) {
    // 初始化 Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // 运行所有测试用例
    return RUN_ALL_TESTS();
}
