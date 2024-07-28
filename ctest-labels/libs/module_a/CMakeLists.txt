cmake_minimum_required(VERSION 3.28)

project(test_ctest_labels)

set(SOURCE_LIB module_a.cpp)

add_library(module_a STATIC ${SOURCE_LIB})

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(t)
endif()
