#include <ring-buffer.hpp>

#define BOOST_TEST_MODULE Test ring-buffer
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(push)

BOOST_AUTO_TEST_CASE(push_expect_first_idx)
{
    RingBuffer<int, 5> rb;
    rb.push(5);
    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 0);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 1);
}

BOOST_AUTO_TEST_CASE(overflow_push_expect_zero_idx_and_catch_up)
{
    RingBuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);
    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 0);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 0);
    BOOST_CHECK_EQUAL(rb.get_catch_up(), true);
}

BOOST_AUTO_TEST_CASE(after_overflow_push_expect_first_idx_and_catch_up)
{
    RingBuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);
    rb.push(4);
    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 1);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 1);
    BOOST_CHECK_EQUAL(rb.get_catch_up(), true);
}

BOOST_AUTO_TEST_SUITE_END()
