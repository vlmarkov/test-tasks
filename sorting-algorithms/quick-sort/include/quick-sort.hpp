#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include <vector>


template<typename T>
static int partition_(std::vector<T>& v, int l, int r)
{
    const auto x = v[r];
    auto less = l;

    for (auto i = l; i < r; ++i)
    {
        if (v[i] <= x)
        {
            std::swap(v[i], v[less]);
            ++less;
        }
    }
    std::swap(v[less], v[r]);
    return less;
}

template<typename T>
static void quick_sort_(std::vector<T>& v, int l, int r)
{
    if (l < r)
    {
        auto q = partition_(v, l, r);
        quick_sort_(v, l, q - 1);
        quick_sort_(v, q + 1, r);
    }
}

template<typename T>
void quick_sort(std::vector<T>& v) // nlogn -> O(n^2)
{
    if (!v.empty())
    {
        quick_sort_(v, 0, v.size() - 1);
    }
}

#endif /* _QUICK_SORT_H_ */
