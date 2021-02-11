#ifndef _SELECTION_SORT_H_
#define _SELECTION_SORT_H_

#include <vector>


template<typename T>
void selection_sort(std::vector<T>& v) // O(n2)
{
    for (size_t i = 0; i + 1 < v.size(); ++i)
    {
        auto min = i;
        for (size_t j = i + 1; j < v.size(); ++j)
        {
            if (v[j] < v[min])
            {
                
                min = j;
            }
        }
        std::swap(v[i], v[min]);
    }
}

#endif /* _SELECTION_SORT_H_ */
