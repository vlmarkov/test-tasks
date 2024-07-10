cmake_minimum_required(VERSION 3.28)

project(test_scheduler LANGUAGES CXX)

set(EXE_FILE main)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(${EXE_FILE} main.cpp)

add_compile_options(-Wall -Werror -Wextra -Wpedantic -O3)

target_compile_features(${EXE_FILE} PRIVATE cxx_std_23) 
target_link_libraries(${EXE_FILE} PRIVATE Threads::Threads)
