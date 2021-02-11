#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <binary-search-tree.h>


void test_add_expect_size_one(void **state)
{
    (void) state; /* unused */
    tree_t *ptr = tree_create();

    assert_int_equal(tree_add(ptr, 5, "5"), 0);
    assert_int_equal(ptr->root ? 1 : 0, 1);
    assert_int_equal(tree_size(ptr), 1);

    tree_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_add_expect_size_one),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}