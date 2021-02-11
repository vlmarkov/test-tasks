#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <linked-list.h>


void test_pop_expect_size_zero_invalid_value(void **state)
{
    (void) state; /* unused */
    double_linked_list_t *ptr = double_linked_list_create();
    int ret = double_linked_list_pop_top(ptr);

    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->size, 0);
    assert_int_equal(-1, ret);

    double_linked_list_destroy(&ptr);
}

void test_pop_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    double_linked_list_t *ptr = double_linked_list_create();
    double_linked_list_push_top(ptr, 5);
    int ret = double_linked_list_pop_top(ptr);

    assert_int_equal(ptr->head, NULL);
    assert_int_equal(double_linked_list_size(ptr), 0);
    assert_int_equal(5, ret);

    double_linked_list_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_pop_expect_size_zero_invalid_value),
        cmocka_unit_test(test_pop_expect_size_zero_valid_value),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}