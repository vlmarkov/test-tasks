cmake_minimum_required(VERSION 3.15)

set(lib_name double-ended-queue-lib)
set(lib_srcs queue.cpp)

add_library(${lib_name} STATIC ${lib_srcs})

target_include_directories(${lib_name} PRIVATE ../include)
target_compile_options(${lib_name} PRIVATE "-Wall" "-Werror" "-O3")
