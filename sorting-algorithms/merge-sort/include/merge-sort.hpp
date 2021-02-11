#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include <vector>

template<typename T>
static void merge_sort_(std::vector<T>& v, std::vector<T>& copy, int l, int r)
{
    if (l < r)
    {
        auto middle = (l + r) / 2;
        merge_sort_(v, copy, l, middle);
        merge_sort_(v, copy, middle + 1, r);

        auto k = l;
        for (auto i = l, j = middle + 1; i <= middle || j <= r; ++k)
        {
            if (j > r || (i <= middle && v[i] < v[j]))
            {
                copy[k] = v[i];
                ++i;
            }
            else
            {
                copy[k] = v[j];
                ++j;
            }
        }

        for (auto i = l; i <= r; ++i)
        {
            v[i] = copy[i];
        }
    }
}

template<typename T>
void merge_sort(std::vector<T>& v) // O(nlogn)
{
    if (!v.empty())
    {
        auto copy = v;
        merge_sort_(v, copy, 0, v.size() - 1);
    }
}

#endif /* _MERGE_SORT_H_ */
