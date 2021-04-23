#include <stack.hpp>

#define BOOST_TEST_MODULE Test ring-buffer
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_pop_expect_size_zero_invalid_value)
{
    Stack stack;
    BOOST_CHECK_EQUAL(stack.pop(), -1);
    BOOST_CHECK_EQUAL(stack.size(), 0);
    BOOST_CHECK_EQUAL(stack.empty(), true);
}

BOOST_AUTO_TEST_CASE(test_pop_expect_size_zero_valid_value)
{
    Stack stack;
    stack.push(5);

    BOOST_CHECK_EQUAL(stack.pop(), 5);
    BOOST_CHECK_EQUAL(stack.size(), 0);
    BOOST_CHECK_EQUAL(stack.empty(), true);
}
