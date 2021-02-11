#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>

#include <stdio.h>
#include <string.h>

#include <cmocka.h>
#include <ring-buffer.h>


void test_push_expect_move_ptr(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(5);
    ring_buffer_push(ptr, 1);

    assert_int_equal(ptr->buffer + 1, ptr->head);
    assert_int_equal(ptr->buffer, ptr->tail);

    ring_buffer_destroy(&ptr);
}

void test_push_expect_move_ptr_to_begin_tail_begin(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(5);
    ring_buffer_push(ptr, 1);
    ring_buffer_push(ptr, 2);
    ring_buffer_push(ptr, 3);
    ring_buffer_push(ptr, 4);
    ring_buffer_push(ptr, 5);

    assert_int_equal(ptr->buffer, ptr->head);
    assert_int_equal(ptr->buffer, ptr->tail);

    ring_buffer_destroy(&ptr);
}

void test_push_expect_move_haed_and_tail(void **state)
{
    (void) state; /* unused */
    ring_buffer_t *ptr = ring_buffer_create(5);
    ring_buffer_push(ptr, 1);
    ring_buffer_push(ptr, 2);
    ring_buffer_push(ptr, 3);
    ring_buffer_push(ptr, 4);
    ring_buffer_push(ptr, 5);
    ring_buffer_push(ptr, 6);

    assert_int_equal(ptr->buffer + 1, ptr->head);
    assert_int_equal(ptr->buffer + 1, ptr->tail);

    ring_buffer_destroy(&ptr);
}

int main(void)
{
    const struct CMUnitTest push_tests[] = {
        cmocka_unit_test(test_push_expect_move_ptr),
        cmocka_unit_test(test_push_expect_move_ptr_to_begin_tail_begin),
        cmocka_unit_test(test_push_expect_move_haed_and_tail),
    };

    return cmocka_run_group_tests(push_tests, NULL, NULL);
}
