cmake_minimum_required(VERSION 3.28)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_test_module_a_small  test_module_a_small.cpp)
add_executable(run_test_module_a_medium test_module_a_medium.cpp)
add_executable(run_test_module_a_large  test_module_a_large.cpp)

add_test(NAME run_test_module_a_small  COMMAND run_test_module_a_small)
add_test(NAME run_test_module_a_medium COMMAND run_test_module_a_medium)
add_test(NAME run_test_module_a_large  COMMAND run_test_module_a_large)

set_tests_properties(run_test_module_a_small  PROPERTIES LABELS "small")
set_tests_properties(run_test_module_a_medium PROPERTIES LABELS "medium")
set_tests_properties(run_test_module_a_large  PROPERTIES LABELS "large")

# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(run_test_module_a_small  module_a)
target_link_libraries(run_test_module_a_medium module_a)
target_link_libraries(run_test_module_a_large  module_a)

target_link_libraries(run_test_module_a_small  ${GTEST_LIBRARIES} pthread)
target_link_libraries(run_test_module_a_medium ${GTEST_LIBRARIES} pthread)
target_link_libraries(run_test_module_a_large  ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(run_test_module_a_small)
gtest_discover_tests(run_test_module_a_medium)
gtest_discover_tests(run_test_module_a_large)
