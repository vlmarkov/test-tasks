cmake_minimum_required(VERSION 3.28)

project(test_ctest_labels)

set(SOURCE_LIB module_b.cpp)

add_library(module_b STATIC ${SOURCE_LIB})

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(t)
endif()
