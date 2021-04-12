#ifndef _INSERTION_SORT_H_
#define _INSERTION_SORT_H_

#include <vector>


template<typename T>
void insertion_sort(std::vector<T>& v) // O(n^2)
{
    for (size_t i = 0; i + 1 < v.size(); ++i)
    {
        const auto x = v[i];
        auto j = i;
        while (j > 0 && v[j - 1] > x)
        {
            std::swap(v[j], v[j - 1]);
            --j;
        }
    }
}

#endif /* _INSERTION_SORT_H_ */
