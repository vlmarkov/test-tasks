#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <ring-buffer.h>


void test_destroy_expect_null(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(10);
    ring_buffer_destroy(&ptr);
    assert_int_equal(NULL, ptr);
}

int main(void)
{
    const struct CMUnitTest destroy_tests[] = {
        cmocka_unit_test(test_destroy_expect_null),
    };

    return cmocka_run_group_tests(destroy_tests, NULL, NULL);
}
