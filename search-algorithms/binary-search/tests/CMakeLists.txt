cmake_minimum_required(VERSION 3.15)

project(tests CXX)

find_package(Boost 1.56 REQUIRED COMPONENTS unit_test_framework)
message(STATUS "Using boost ${Boost_VERSION}")

set(src_search search.cpp)

add_executable(test-search ${src_search})

foreach(_target test-search)
    target_link_libraries(${_target} Boost::unit_test_framework)
    target_compile_features(${_target} PRIVATE cxx_std_20)
    target_compile_options(${_target} PRIVATE "-Wall" "-Werror" "-O3")
    target_include_directories(${_target} PRIVATE ../include)
    add_test(NAME ${_target} COMMAND ${_target})
endforeach()
