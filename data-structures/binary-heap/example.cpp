#include <binary-heap.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    {
        BinaryHeap<int, 10, HeapType::max> heap;
        heap.insert(1);
        heap.insert(4);
        heap.insert(2);
        heap.insert(3);
        heap.insert(9);
        heap.insert(7);
        heap.insert(8);
        heap.insert(10);
        heap.insert(14);
        heap.insert(16);
        heap.remove();
        std::cout << heap << std::endl;
    }

    {
        BinaryHeap<int, 10, HeapType::min> heap;
        heap.insert(16);
        heap.insert(14);
        heap.insert(10);
        heap.insert(8);
        heap.insert(7);
        heap.insert(9);
        heap.insert(3);
        heap.insert(2);
        heap.insert(4);
        heap.insert(1);
        heap.remove();
        std::cout << heap << std::endl;
    }

    
    return 0;
}
