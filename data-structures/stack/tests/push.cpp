#include <stack.hpp>

#define BOOST_TEST_MODULE Test push stack
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_push_expect_size_one)
{
    Stack stack;
    stack.push(1);

    BOOST_CHECK_EQUAL(stack.top(), 1);
    BOOST_CHECK_EQUAL(stack.size(), 1);
    BOOST_CHECK_EQUAL(stack.empty(), false);
}
