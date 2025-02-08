enable_testing()

# 找到 gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 创建可执行文件
add_executable(runTests test_server.cpp)
target_link_libraries(runTests PRIVATE ${GTEST_LIBRARIES} pthread server)

add_executable(callbackTests test_callback.cpp)
target_link_libraries(callbackTests PRIVATE ${GTEST_LIBRARIES})

add_executable(anyTests test_any.cpp)
target_link_libraries(anyTests PRIVATE ${GTEST_LIBRARIES})

add_executable(configTests test_config.cpp)
target_link_libraries(configTests PRIVATE ${GTEST_LIBRARIES})

add_executable(variantTests test_variant.cpp)
target_link_libraries(variantTests PRIVATE ${GTEST_LIBRARIES})

add_executable(tupleTests test_tuple.cpp)
target_link_libraries(tupleTests PRIVATE ${GTEST_LIBRARIES})

add_executable(decltypeTests test_decltype.cpp)
target_link_libraries(decltypeTests PRIVATE ${GTEST_LIBRARIES})

add_executable(lambdaTests test_lambda_bind.cpp)
target_link_libraries(lambdaTests PRIVATE ${GTEST_LIBRARIES})

add_executable(alloctorTests test_alloctor.cpp)
target_link_libraries(alloctorTests PRIVATE ${GTEST_LIBRARIES})

add_executable(optionalTests test_optional.cpp)
target_link_libraries(optionalTests PRIVATE ${GTEST_LIBRARIES})

add_executable(promiseFutureTests test_promise_future.cpp)
target_link_libraries(promiseFutureTests PRIVATE ${GTEST_LIBRARIES})

add_executable(queueTests test_queue.cpp)
target_link_libraries(queueTests PRIVATE ${GTEST_LIBRARIES})

add_executable(chronoTests test_chrono.cpp)
target_link_libraries(chronoTests PRIVATE ${GTEST_LIBRARIES})

add_executable(LRUTests test_cache.cpp)
target_link_libraries(LRUTests PRIVATE ${GTEST_LIBRARIES})

# 添加测试
add_test(NAME ServerTest COMMAND runTests)
add_test(NAME CallbackTest COMMAND callbackTests)
add_test(NAME AnyTests COMMAND anyTests)
add_test(NAME TestConfigs COMMAND configTests)
add_test(NAME TestVariants COMMAND variantTests)
add_test(NAME FSMTest COMMAND variantTests)
add_test(NAME TestTuples COMMAND tupleTests)
add_test(NAME DecltypeTests COMMAND decltypeTests)
add_test(NAME BindTests COMMAND lambdaTests)
add_test(NAME LambdaTests COMMAND lambdaTests)
add_test(NAME AlloctorTests COMMAND lambdaTests)
add_test(NAME OptionalTests COMMAND optionalTests)
add_test(NAME PromiseFutureTests COMMAND promiseFutureTests)
add_test(NAME QueueTests COMMAND queueTests)
add_test(NAME TestsChrono COMMAND chronoTests)
add_test(NAME LRUTests COMMAND SafeLRUCacheTests)
