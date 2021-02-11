#include <ring-buffer.hpp>

#define BOOST_TEST_MODULE Test ring-buffer
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(pop)

BOOST_AUTO_TEST_CASE(pop_expect_empty_and_zero_idx)
{
    RingBuffer<int, 5> rb;
    auto ret = rb.pop();

    BOOST_CHECK_EQUAL(ret, 0);
    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 0);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 0);
}

BOOST_AUTO_TEST_CASE(pop_expect_value_and_first_idx)
{
    RingBuffer<int, 5> rb;
    rb.push(5);
    auto ret = rb.pop();

    BOOST_CHECK_EQUAL(ret, 5);
    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 1);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 1);
}

BOOST_AUTO_TEST_CASE(multiple_pop_expect_first_idx)
{
    RingBuffer<int, 5> rb;
    rb.push(5);
    rb.pop();
    rb.pop();

    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 1);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 1);
}

BOOST_AUTO_TEST_CASE(after_overflow_push_pop_expect_zero_idx)
{
    RingBuffer<int, 3> rb;
    rb.push(1);
    rb.push(2);
    rb.push(3);

    BOOST_CHECK_EQUAL(rb.pop(), 1);
    BOOST_CHECK_EQUAL(rb.pop(), 2);
    BOOST_CHECK_EQUAL(rb.pop(), 3);

    BOOST_CHECK_EQUAL(rb.get_tail_idx(), 0);
    BOOST_CHECK_EQUAL(rb.get_head_idx(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
