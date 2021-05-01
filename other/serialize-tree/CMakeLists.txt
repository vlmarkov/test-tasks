cmake_minimum_required(VERSION 3.16.3)

project(serialize-tree)

enable_testing()

include_directories(src)

add_subdirectory(src src)
add_subdirectory(tests tests)