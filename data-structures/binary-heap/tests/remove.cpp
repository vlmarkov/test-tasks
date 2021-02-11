#include <binary-heap.hpp>

#define BOOST_TEST_MODULE Test binary-heap
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(remove_operation)

BOOST_AUTO_TEST_CASE(max_heap_remove)
{
    BinaryHeap<int, 5, HeapType::max> bh;
    bh.insert(1);
    bh.insert(2);
    bh.insert(3);
    bh.insert(5);

    BOOST_CHECK_EQUAL(bh.remove(), 5);
    BOOST_CHECK_EQUAL(bh.top(), 3);
    BOOST_CHECK_EQUAL(bh.capacity(), 3);
}

BOOST_AUTO_TEST_CASE(min_heap_remove)
{
    BinaryHeap<int, 5, HeapType::min> bh;
    bh.insert(5);
    bh.insert(3);
    bh.insert(2);
    bh.insert(1);

    BOOST_CHECK_EQUAL(bh.remove(), 1);
    BOOST_CHECK_EQUAL(bh.top(), 2);
    BOOST_CHECK_EQUAL(bh.capacity(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
