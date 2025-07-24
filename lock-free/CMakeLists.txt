cmake_minimum_required(VERSION 3.28)

project(MultiThreadTest)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 23) 
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

enable_testing()

add_library(lock-free-list-lib SHARED lock_free_list.cpp)
add_library(scheduler-lib SHARED scheduler.cpp)

add_subdirectory(tests)
