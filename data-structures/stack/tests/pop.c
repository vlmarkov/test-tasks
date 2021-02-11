#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <stack.h>


void test_pop_expect_size_zero_invalid_value(void **state)
{
    (void) state; /* unused */
    stack_t *ptr = stack_create();
    int ret = stack_pop(ptr);

    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->size, 0);
    assert_int_equal(-1, ret);

    stack_destroy(&ptr);
}

void test_pop_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    stack_t *ptr = stack_create();
    stack_push(ptr, 5);
    int ret = stack_pop(ptr);

    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->size, 0);
    assert_int_equal(5, ret);

    stack_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_pop_expect_size_zero_invalid_value),
        cmocka_unit_test(test_pop_expect_size_zero_valid_value),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}