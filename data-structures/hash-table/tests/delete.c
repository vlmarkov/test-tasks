#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <hash-table.h>


void test_delete_expect_success(void **state)
{
    (void) state; /* unused */
    hash_table_t *ptr = hash_table_create(10);
    assert_int_equal(hash_table_add(ptr, 10), 0);
    assert_int_equal(hash_table_delete(ptr, 10), 0);
    assert_int_equal(ptr->capacity, 0);
    hash_table_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest destroy_tests[] = {
        cmocka_unit_test(test_delete_expect_success),
    };

    return cmocka_run_group_tests(destroy_tests, NULL, NULL);
}
