cmake_minimum_required(VERSION 3.15)

project(selection-sort CXX)

set(exec_name example)

add_executable(${exec_name} example.cpp)
target_include_directories(${exec_name} PRIVATE ./include)

target_compile_features(${exec_name} PRIVATE cxx_std_20)

target_compile_options(${exec_name} PRIVATE "-Wall" "-Werror" "-O3")

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
