cmake_minimum_required(VERSION 3.15)

project(tests C)

find_package(Cmocka REQUIRED)
message(STATUS "Using cmocka ${Cmocka_VERSION}")

set(src_destroy destroy.c)
set(src_push    push.c)
set(src_pop     pop.c)

add_executable(test-destroy ${src_destroy})
add_executable(test-push    ${src_push})
add_executable(test-pop     ${src_pop})

foreach(_target test-destroy test-push test-pop)
    target_link_libraries(${_target} stack-lib
                                     ${CMOCKA_LIBRARY})
    target_compile_options(${_target} PRIVATE "-Wall" "-Werror" "-O3")
    target_include_directories(${_target} PRIVATE ../include)
    add_test(NAME ${_target} COMMAND ${_target})
endforeach()
