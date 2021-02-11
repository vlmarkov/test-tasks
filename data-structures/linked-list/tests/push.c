#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <linked-list.h>


void test_push_expect_size_one(void **state)
{
    (void) state; /* unused */
    double_linked_list_t *ptr = double_linked_list_create();
    double_linked_list_push_top(ptr, 1);

    assert_int_equal(ptr->size, 1);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->head->next ? 1 : 0, 0);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);

    double_linked_list_destroy(&ptr);
}

void test_push_expect_size_two(void **state)
{
    (void) state; /* unused */
    double_linked_list_t *ptr = double_linked_list_create();
    double_linked_list_push_top(ptr, 1);
    double_linked_list_push_top(ptr, 2);

    assert_int_equal(double_linked_list_size(ptr), 2);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->head->next ? 1 : 0, 1);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);
    assert_int_equal(ptr->head->next->next ? 1 : 0, 0);
    assert_int_equal(ptr->head->next->prev ? 1 : 0, 1);

    double_linked_list_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest push_tests[] = {
        cmocka_unit_test(test_push_expect_size_one),
        cmocka_unit_test(test_push_expect_size_two),
    };

    return cmocka_run_group_tests(push_tests, NULL, NULL);
}
