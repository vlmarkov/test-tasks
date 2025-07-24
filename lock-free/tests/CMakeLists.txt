add_executable(lock_free_list_tests lock_free_list_test.cpp)
add_executable(scheduler_tests scheduler_test.cpp)

target_link_libraries(lock_free_list_tests GTest::gtest_main
                                           lock-free-list-lib)

target_link_libraries(scheduler_tests GTest::gtest_main
                                      scheduler-lib
                                      lock-free-list-lib)

include(GoogleTest)
gtest_discover_tests(lock_free_list_tests scheduler_tests)
gtest_discover_tests(scheduler_tests)
