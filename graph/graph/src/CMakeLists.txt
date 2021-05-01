cmake_minimum_required(VERSION 3.15)

set(lib_name graph-lib)
set(lib_srcs graph.cpp)

add_library(${lib_name} STATIC ${lib_srcs})

target_include_directories(${lib_name} PRIVATE ../include)
target_compile_options(${lib_name} PRIVATE "-Wall" "-Werror" "-O3")
