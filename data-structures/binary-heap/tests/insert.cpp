#include <binary-heap.hpp>

#define BOOST_TEST_MODULE Test binary-heap
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(insert_operation)

BOOST_AUTO_TEST_CASE(max_heap_insert)
{
    BinaryHeap<int, 5, HeapType::max> bh;
    bh.insert(1);
    bh.insert(2);

    BOOST_CHECK_EQUAL(bh.top(), 2);
    BOOST_CHECK_EQUAL(bh.capacity(), 2);
}

BOOST_AUTO_TEST_CASE(min_heap_insert)
{
    BinaryHeap<int, 5, HeapType::min> bh;
    bh.insert(2);
    bh.insert(1);

    BOOST_CHECK_EQUAL(bh.top(), 1);
    BOOST_CHECK_EQUAL(bh.capacity(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
