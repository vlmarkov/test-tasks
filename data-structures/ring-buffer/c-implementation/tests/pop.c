#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <ring-buffer.h>


void test_pop_without_push_expect_empty(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(10);
    int ret = ring_buffer_pop(ptr);

    assert_int_equal(ptr->head, ptr->tail);
    assert_int_equal(-1, ret);

    ring_buffer_destroy(&ptr);
}

void test_pop_after_push_expect_value(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(10);
    ring_buffer_push(ptr, 5);
    int ret = ring_buffer_pop(ptr);

    assert_int_equal(ptr->buffer + 1, ptr->tail);
    assert_int_equal(ptr->head, ptr->tail);
    assert_int_equal(5, ret);

    ring_buffer_destroy(&ptr);
}

void test_pop_after_overflow_push_expect_value(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(3);
    ring_buffer_push(ptr, 1);
    ring_buffer_push(ptr, 2);
    ring_buffer_push(ptr, 3);

    assert_int_equal(ptr->buffer, ptr->head);
    assert_int_equal(ptr->buffer, ptr->tail);
    assert_int_equal(true, ptr->catch_up);

    int ret = ring_buffer_pop(ptr);
    assert_int_equal(1, ret);

    assert_int_equal(ptr->buffer, ptr->head);
    assert_int_equal(ptr->buffer + 1, ptr->tail);
    assert_int_equal(false, ptr->catch_up);

    ret = ring_buffer_pop(ptr);
    assert_int_equal(2, ret);

    assert_int_equal(ptr->buffer, ptr->head);
    assert_int_equal(ptr->buffer + 2, ptr->tail);
    assert_int_equal(false, ptr->catch_up);

    ret = ring_buffer_pop(ptr);
    assert_int_equal(3, ret);

    assert_int_equal(ptr->buffer, ptr->head);
    assert_int_equal(ptr->buffer, ptr->tail);
    assert_int_equal(false, ptr->catch_up);

    ret = ring_buffer_pop(ptr);
    assert_int_equal(-1, ret);

    assert_int_equal(ptr->buffer, ptr->tail);
    assert_int_equal(ptr->head, ptr->tail);
    assert_int_equal(false, ptr->catch_up);

    ring_buffer_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest pop_tests[] = {
        cmocka_unit_test(test_pop_without_push_expect_empty),
        cmocka_unit_test(test_pop_after_push_expect_value),
        cmocka_unit_test(test_pop_after_overflow_push_expect_value),
    };

    return cmocka_run_group_tests(pop_tests, NULL, NULL);
}