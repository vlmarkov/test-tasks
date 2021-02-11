#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <binary-search-tree.h>


void test_delete_expect_error(void **state)
{
    (void) state; /* unused */
    tree_t *ptr = tree_create();

    assert_int_equal(tree_delete(ptr, 5), -1);
    assert_int_equal(ptr->root ? 1 : 0, 0);
    assert_int_equal(tree_size(ptr), 0);

    tree_destroy(&ptr);
}

void test_delete_expect_success(void **state)
{
    (void) state; /* unused */
    tree_t *ptr = tree_create();

    assert_int_equal(tree_add(ptr, 5, "5"), 0);
    assert_int_equal(tree_delete(ptr, 5), 0);
    assert_int_equal(ptr->root ? 1 : 0, 0);
    assert_int_equal(tree_size(ptr), 0);

    tree_destroy(&ptr);
}


int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_delete_expect_error),
        cmocka_unit_test(test_delete_expect_success),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}