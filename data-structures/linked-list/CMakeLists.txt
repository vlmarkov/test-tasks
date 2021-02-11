cmake_minimum_required(VERSION 3.15)

project(stack C)

set(exec_name double-linked-list)

add_subdirectory(src)

add_executable(${exec_name} example.c)
target_include_directories(${exec_name} PRIVATE ./include)

target_compile_options(${exec_name} PRIVATE "-Wall" "-Werror" "-O3")
target_link_libraries(${exec_name} linked-list-lib)

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
