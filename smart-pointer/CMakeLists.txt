cmake_minimum_required(VERSION 3.15)

project(smart-pointer CXX)

set(exec_name smart-pointer)

add_executable(${exec_name} example.cpp)
target_include_directories(${exec_name} PRIVATE ./include)

target_compile_options(${exec_name} PRIVATE "-Wall" "-Werror" "-O3")

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
