#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

class Config {
  public:
    void set(const std::string &key, const std::string &value) {
        config_[key] = value;
    }

    std::string get(const std::string &key) const {
        auto it = config_.find(key);
        if (it != config_.end()) {
            return it->second;
        }
        throw std::runtime_error("Key not found");
    }

    bool contains(const std::string &key) const {
        return config_.find(key) != config_.end();
    }

    void remove(const std::string &key) { config_.erase(key); }

    void clear() { config_.clear(); }

  private:
    std::unordered_map<std::string, std::string> config_;
};

class ConfigTest : public ::testing::Test {
  protected:
    Config config;

    void SetUp() override {
        config.set("key1", "value1");
        config.set("key2", "value2");
    }
};

TEST_F(ConfigTest, SetAndGet) {
    EXPECT_EQ(config.get("key1"), "value1");
    EXPECT_EQ(config.get("key2"), "value2");
}

TEST_F(ConfigTest, Contains) {
    EXPECT_TRUE(config.contains("key1"));
    EXPECT_FALSE(config.contains("key3"));
}

TEST_F(ConfigTest, Remove) {
    config.remove("key1");
    EXPECT_FALSE(config.contains("key1"));
}

TEST_F(ConfigTest, Clear) {
    config.clear();
    EXPECT_FALSE(config.contains("key1"));
    EXPECT_FALSE(config.contains("key2"));
}

TEST_F(ConfigTest, GetNonExistentKey) {
    EXPECT_THROW(config.get("key3"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
