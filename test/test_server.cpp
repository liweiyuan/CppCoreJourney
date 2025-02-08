#include <future>
#include <gtest/gtest.h>
#include <string>
#include <thread>

class Server {
  public:
    void start() {
        running = true;
        server_thread = std::thread([this]() {
            while (running) {
                // Simulate server work
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }

    void stop() {
        running = false;
        if (server_thread.joinable()) {
            server_thread.join();
        }
    }

    bool isRunning() const { return running; }

  private:
    bool running = false;
    std::thread server_thread;
};

class ServerTest : public ::testing::Test {
  protected:
    Server server;

    void SetUp() override { server.start(); }

    void TearDown() override { server.stop(); }
};

TEST_F(ServerTest, StartAndStop) {
    EXPECT_TRUE(server.isRunning());
    server.stop();
    EXPECT_FALSE(server.isRunning());
}

TEST_F(ServerTest, ServerThreadJoinable) {
    EXPECT_TRUE(server.isRunning());
    server.stop();
    EXPECT_FALSE(server.isRunning());
}

TEST_F(ServerTest, ServerRunning) {
    EXPECT_TRUE(server.isRunning());
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    EXPECT_TRUE(server.isRunning());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
