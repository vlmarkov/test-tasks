#include <linked-list.hpp>

#define BOOST_TEST_MODULE Test linked-list
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(test_push_expect_size_one)
{
    LinkedList ll;

    ll.push_front(1);

    BOOST_CHECK_EQUAL(ll.size(), 1);
    BOOST_CHECK_EQUAL(ll.empty(), false);
    BOOST_CHECK_EQUAL(ll.pop_front(), 1);
}

BOOST_AUTO_TEST_CASE(test_push_expect_size_two)
{
    LinkedList ll;

    ll.push_front(1);
    ll.push_front(2);

    BOOST_CHECK_EQUAL(ll.size(), 2);
    BOOST_CHECK_EQUAL(ll.empty(), false);
    BOOST_CHECK_EQUAL(ll.pop_front(), 2);
    BOOST_CHECK_EQUAL(ll.pop_front(), 1);
}
