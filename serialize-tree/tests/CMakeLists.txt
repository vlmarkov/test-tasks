project(tests)

set(test_source tests.cpp)
add_executable(test-tree ${test_source})

target_link_libraries(test-tree
                      tree-lib
                      parser-lib
                      node-lib
                      exception-lib)

add_test(NAME test-tree COMMAND test-tree)
