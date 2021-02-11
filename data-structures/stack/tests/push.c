#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <stack.h>


void test_push_expect_size_one(void **state)
{
    (void) state; /* unused */
    stack_t *ptr = stack_create();
    stack_push(ptr, 1);

    assert_int_equal(ptr->size, 1);
    assert_int_equal(ptr->head ? 1 : 0, 1);

    stack_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest push_tests[] = {
        cmocka_unit_test(test_push_expect_size_one),
    };

    return cmocka_run_group_tests(push_tests, NULL, NULL);
}
