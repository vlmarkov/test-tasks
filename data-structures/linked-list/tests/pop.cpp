#include <linked-list.hpp>

#define BOOST_TEST_MODULE Test linked-list
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_pop_expect_size_zero_invalid_value)
{
    LinkedList ll;

    BOOST_CHECK_EQUAL(ll.pop_front(), -1);
    BOOST_CHECK_EQUAL(ll.size(), 0);
    BOOST_CHECK_EQUAL(ll.empty(), true);
}

BOOST_AUTO_TEST_CASE(test_pop_expect_size_zero_valid_value)
{
    LinkedList ll;
    ll.push_front(5);

    BOOST_CHECK_EQUAL(ll.pop_front(), 5);
    BOOST_CHECK_EQUAL(ll.size(), 0);
    BOOST_CHECK_EQUAL(ll.empty(), true);    
}
