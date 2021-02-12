#include <binary-search.hpp>

#define BOOST_TEST_MODULE Test binary-search
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(search)

BOOST_AUTO_TEST_CASE(search)
{
    std::vector<int> v{-45, -5, 0, 5, 9, 33};
    BOOST_CHECK_EQUAL(binary_search(v, 0), 0);
    BOOST_CHECK_EQUAL(binary_search(v, 99), -1);
}

BOOST_AUTO_TEST_SUITE_END()
