cmake_minimum_required(VERSION 3.20)
project(CppCoreJourney)

set(CMAKE_CXX_STANDARD 17)

# 包含头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加静态库
add_library(server STATIC src/server.cpp)

# 添加主程序
add_executable(main src/main.cpp)

# 链接库
target_link_libraries(main PRIVATE server)

# 添加测试目录（如果有 tests/CMakeLists.txt）
add_subdirectory(tests)