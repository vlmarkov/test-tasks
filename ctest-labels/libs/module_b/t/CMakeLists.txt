cmake_minimum_required(VERSION 3.28)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_test_module_b_small  test_module_b_small.cpp)
add_executable(run_test_module_b_medium test_module_b_medium.cpp)
add_executable(run_test_module_b_large  test_module_b_large.cpp)

add_test(NAME run_test_module_b_small  COMMAND run_test_module_b_small)
add_test(NAME run_test_module_b_medium COMMAND run_test_module_b_medium)
add_test(NAME run_test_module_b_large  COMMAND run_test_module_b_large)

set_tests_properties(run_test_module_b_small  PROPERTIES LABELS "small")
set_tests_properties(run_test_module_b_medium PROPERTIES LABELS "medium")
set_tests_properties(run_test_module_b_large  PROPERTIES LABELS "large")

# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(run_test_module_b_small  module_b)
target_link_libraries(run_test_module_b_medium module_b)
target_link_libraries(run_test_module_b_large  module_b)

target_link_libraries(run_test_module_b_small  ${GTEST_LIBRARIES} pthread)
target_link_libraries(run_test_module_b_medium ${GTEST_LIBRARIES} pthread)
target_link_libraries(run_test_module_b_large  ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(run_test_module_b_small)
gtest_discover_tests(run_test_module_b_medium)
gtest_discover_tests(run_test_module_b_large)
