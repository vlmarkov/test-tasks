#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <queue.h>


void test_pop_top_expect_size_zero_invalid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();

    assert_int_equal(double_ended_queue_pop_top(ptr), -1);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);    

    double_ended_queue_destroy(&ptr);
}

void test_pop_tail_expect_size_zero_invalid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();

    assert_int_equal(double_ended_queue_pop_tail(ptr), -1);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);    

    double_ended_queue_destroy(&ptr);
}

void test_pop_top_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_top(ptr, 5);

    assert_int_equal(double_ended_queue_pop_top(ptr), 5);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);

    double_ended_queue_destroy(&ptr);
}

void test_pop_pop_top_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_top(ptr, 1);
    double_ended_queue_push_top(ptr, 2);

    assert_int_equal(double_ended_queue_pop_top(ptr), 2);
    assert_int_equal(double_ended_queue_pop_top(ptr), 1);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);

    double_ended_queue_destroy(&ptr);
}

void test_pop_tail_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_tail(ptr, 5);

    assert_int_equal(double_ended_queue_pop_tail(ptr), 5);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);   

    double_ended_queue_destroy(&ptr);
}

void test_pop_pop_tail_expect_size_zero_valid_value(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_tail(ptr, 1);
    double_ended_queue_push_tail(ptr, 2);

    assert_int_equal(double_ended_queue_pop_tail(ptr), 2);
    assert_int_equal(double_ended_queue_pop_tail(ptr), 1);
    assert_int_equal(double_ended_queue_size(ptr), 0);
    assert_int_equal(ptr->head, NULL);
    assert_int_equal(ptr->tail, NULL);

    double_ended_queue_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_pop_top_expect_size_zero_invalid_value),
        cmocka_unit_test(test_pop_tail_expect_size_zero_invalid_value),
        cmocka_unit_test(test_pop_top_expect_size_zero_valid_value),
        cmocka_unit_test(test_pop_pop_top_expect_size_zero_valid_value),
        cmocka_unit_test(test_pop_tail_expect_size_zero_valid_value),
        cmocka_unit_test(test_pop_pop_tail_expect_size_zero_valid_value),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}