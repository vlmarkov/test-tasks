#include <counting-sort.hpp>

#define BOOST_TEST_MODULE Test counting-sort
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(sort)

BOOST_AUTO_TEST_CASE(sort)
{
    std::vector<int> v{145, 5, 0, 3, 77, 15, 16, 34};
    counting_sort(v);
    BOOST_CHECK_EQUAL(v[0], 0);
    BOOST_CHECK_EQUAL(v[1], 3);
    BOOST_CHECK_EQUAL(v[2], 5);
    BOOST_CHECK_EQUAL(v[3], 15);
    BOOST_CHECK_EQUAL(v[4], 16);
    BOOST_CHECK_EQUAL(v[5], 34);
    BOOST_CHECK_EQUAL(v[6], 77);
    BOOST_CHECK_EQUAL(v[7], 145);
}

BOOST_AUTO_TEST_SUITE_END()
