#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

#include <vector>


template<typename T>
static void heapify_(std::vector<T>& v, const int n, const int i)
{
    // Find largest among root, left child and right child
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;

    if (left < n && v[left] > v[largest])
    {
        largest = left;
    }

    if (right < n && v[right] > v[largest])
    {
        largest = right;
    }
    // Swap and continue heapifying if root is not largest
    if (largest != i)
    {
        std::swap(v[i], v[largest]);
        heapify_(v, n, largest);
    }
}

template<typename T>
void heap_sort(std::vector<T>& v) // O(nlogn)
{
    if (v.empty())
    {
        return;
    }
    // Build max heap
    for (int i = v.size() / 2 - 1; i >= 0; --i)
    {
        heapify_(v, v.size(), i);
    }
    // Heap sort
    for (int i = v.size() - 1; i >= 0; --i)
    {
        // Move current root to end
        std::swap(v[0], v[i]); 
        // Heapify root element to get highest element at root again
        heapify_(v, i, 0); 
    }
}

#endif /* _HEAP_SORT_H_ */
