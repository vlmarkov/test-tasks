#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <vector>


template<typename T>
void bubble_sort(std::vector<T>& v) // O(n2)
{
    for (size_t i = 0; i + 1 < v.size(); ++i)
    {
        for (size_t j = 0; j + 1 < v.size() - i; ++j)
        {
            if (v[j + 1] < v[j])
            {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

template<typename T>
void bubble_sort_v2(std::vector<T>& v) // O(n2)
{
    auto swapped = false;
    do
    {
        swapped = false;
        for (size_t i = 0; i < v.size() - 1; ++i)
        {
            if (v[i] > v[i + 1])
            {
                std::swap(v[i], v[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

#endif /* _BUBBLE_SORT_H_ */
