#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <queue.h>


void test_push_top_expect_size_one(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_top(ptr, 1);

    assert_int_equal(double_ended_queue_size(ptr), 1);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->tail ? 1 : 0, 1);
    assert_int_equal(ptr->head, ptr->tail);
    assert_int_equal(ptr->head->next ? 1 : 0, 0);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);
    assert_int_equal(ptr->tail->next ? 1 : 0, 0);
    assert_int_equal(ptr->tail->prev ? 1 : 0, 0);

    double_ended_queue_destroy(&ptr);
}

void test_push_tail_expect_size_one(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_top(ptr, 1);

    assert_int_equal(double_ended_queue_size(ptr), 1);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->tail ? 1 : 0, 1);
    assert_int_equal(ptr->head, ptr->tail);
    assert_int_equal(ptr->head->next ? 1 : 0, 0);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);
    assert_int_equal(ptr->tail->next ? 1 : 0, 0);
    assert_int_equal(ptr->tail->prev ? 1 : 0, 0);

    double_ended_queue_destroy(&ptr);
}

void test_push_top_expect_size_two(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_top(ptr, 1);
    double_ended_queue_push_top(ptr, 2);

    assert_int_equal(double_ended_queue_size(ptr), 2);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->tail ? 1 : 0, 1);
    assert_int_equal(ptr->head->next ? 1 : 0, 1);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);
    assert_int_equal(ptr->head->next, ptr->tail);
    assert_int_equal(ptr->tail->prev, ptr->head);
    assert_int_equal(ptr->tail->next ? 1 : 0, 0);
    assert_int_equal(ptr->tail->prev ? 1 : 0, 1);

    double_ended_queue_destroy(&ptr);
}

void test_push_tail_expect_size_two(void **state)
{
    (void) state; /* unused */
    double_ended_queue_t *ptr = double_ended_queue_create();
    double_ended_queue_push_tail(ptr, 1);
    double_ended_queue_push_tail(ptr, 2);

    assert_int_equal(double_ended_queue_size(ptr), 2);
    assert_int_equal(ptr->head ? 1 : 0, 1);
    assert_int_equal(ptr->tail ? 1 : 0, 1);
    assert_int_equal(ptr->head->next ? 1 : 0, 1);
    assert_int_equal(ptr->head->prev ? 1 : 0, 0);
    assert_int_equal(ptr->head->next, ptr->tail);
    assert_int_equal(ptr->tail->prev, ptr->head);
    assert_int_equal(ptr->tail->next ? 1 : 0, 0);
    assert_int_equal(ptr->tail->prev ? 1 : 0, 1);

    double_ended_queue_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest push_tests[] = {
        cmocka_unit_test(test_push_top_expect_size_one),
        cmocka_unit_test(test_push_tail_expect_size_one),
        cmocka_unit_test(test_push_top_expect_size_two),
        cmocka_unit_test(test_push_tail_expect_size_two),
    };

    return cmocka_run_group_tests(push_tests, NULL, NULL);
}
