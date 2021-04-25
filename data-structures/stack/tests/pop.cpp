#include <stack.hpp>

#define BOOST_TEST_MODULE Test pop stack
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

BOOST_AUTO_TEST_CASE(test_multiple_pops_expect_size_zero_and_valid_values)
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    BOOST_CHECK_EQUAL(stack.size(), 3);
    BOOST_CHECK_EQUAL(stack.pop(), 3);
    BOOST_CHECK_EQUAL(stack.size(), 2);
    BOOST_CHECK_EQUAL(stack.pop(), 2);
    BOOST_CHECK_EQUAL(stack.size(), 1);
    BOOST_CHECK_EQUAL(stack.pop(), 1);
    BOOST_CHECK_EQUAL(stack.size(), 0);
    BOOST_CHECK_EQUAL(stack.empty(), true);
}
