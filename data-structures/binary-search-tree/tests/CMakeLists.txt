cmake_minimum_required(VERSION 3.15)

project(tests C)

find_package(Cmocka REQUIRED)
message(STATUS "Using cmocka ${Cmocka_VERSION}")

set(src_destroy destroy.c)
set(src_add     add.c)
set(src_delete  delete.c)

add_executable(test-destroy ${src_destroy})
add_executable(test-add     ${src_add})
add_executable(test-delete  ${src_delete})

foreach(_target test-destroy test-add test-delete)
    target_link_libraries(${_target} binary-search-tree-lib ${CMOCKA_LIBRARY})
    target_compile_options(${_target} PRIVATE "-Wall" "-Werror" "-O3")
    target_include_directories(${_target} PRIVATE ../include)
    add_test(NAME ${_target} COMMAND ${_target})
endforeach()
