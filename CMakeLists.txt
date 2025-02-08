cmake_minimum_required(VERSION 3.10)

# 项目名与 C++ 标准设置
project(CppCoreJourney)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# 添加核心代码
add_library(server STATIC src/server.cpp)
#add_library(callback SHARE src/callback.cpp)

# 添加测试目录
add_subdirectory(test)
