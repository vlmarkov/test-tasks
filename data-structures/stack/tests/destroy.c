#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <stack.h>


void test_destroy_expect_null(void **state)
{
    (void) state; /* unused */
    stack_t *stack = stack_create();
    stack_destroy(&stack);
    assert_int_equal(NULL, stack);
}

int main(void)
{
    const struct CMUnitTest destroy_tests[] = {
        cmocka_unit_test(test_destroy_expect_null),
    };

    return cmocka_run_group_tests(destroy_tests, NULL, NULL);
}
