project(tests)

set(test_source_tree tests_tree.cpp)
set(test_source_empty_tree tests_empty_tree.cpp)

add_executable(test-tree ${test_source_tree})
add_executable(test-empty-tree ${test_source_empty_tree})

target_link_libraries(test-tree
                      tree-lib
                      parser-lib
                      node-lib
                      exception-lib)

target_link_libraries(test-empty-tree
                      tree-lib
                      parser-lib
                      node-lib
                      exception-lib)


add_test(NAME test-tree COMMAND test-tree)
add_test(NAME test-empty-tree COMMAND test-empty-tree)