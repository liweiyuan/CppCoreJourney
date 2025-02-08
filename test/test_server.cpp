#include "server.h"
#include <gtest/gtest.h>

// 测试类定义
TEST(ServerTest, HandleRequest) {
  Server server;
  server.handle_request("TestRequest");
  EXPECT_EQ(server.get_last_response(), "Processed: TestRequest");
}

TEST(ServerTest, HandleEmptyRequest) {
  Server server;
  server.handle_request("");
  EXPECT_EQ(server.get_last_response(), "Processed: ");
}

int main(int argc, char **argv) {
  // 初始化 Google Test
  ::testing::InitGoogleTest(&argc, argv);

  // 运行所有测试用例
  return RUN_ALL_TESTS();
}
