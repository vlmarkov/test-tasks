cmake_minimum_required(VERSION 3.28)

project(test_ctest_labels)

set(SOURCE_EXE main.cpp)

add_executable(main ${SOURCE_EXE})

target_link_libraries(main module_a)
target_link_libraries(main module_b)
