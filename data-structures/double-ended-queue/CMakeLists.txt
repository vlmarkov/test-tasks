cmake_minimum_required(VERSION 3.15)

project(double-ended-queue CXX)

set(exec_name example)

add_subdirectory(src)

add_executable(${exec_name} example.cpp)
target_include_directories(${exec_name} PRIVATE ./include)

target_compile_options(${exec_name} PRIVATE "-Wall" "-Werror" "-O3")
target_link_libraries(${exec_name} double-ended-queue-lib)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
