#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include <vector>


template<typename T>
void merge_(std::vector<T>& v, int lb, int middle, int rb)
{
    auto copy = v;
    auto i = lb;
    auto l = lb;
    auto r = middle + 1;

    while (l <= middle && r <= rb)
    {
        if (copy[l] <= copy[r])
        {
            v[i++] = copy[l++];
        }
        else
        {
            v[i++] = copy[r++];
        }
    }

    while (l <= middle)
    {
        v[i++] = copy[l++];
    }

    while (r <= rb)
    {
        v[i++] = copy[r++];
    }
}

template<typename T>
void merge_sort_(std::vector<T>& v, int lb, int rb)
{
    if (lb < rb)
    {
        const auto middle = (lb + rb) / 2;
        merge_sort_(v, lb, middle);
        merge_sort_(v, middle + 1, rb);
        merge_(v, lb, middle, rb);
    }
}

template<typename T>
void merge_sort(std::vector<T>& v) // O(nlogn)
{
    if (!v.empty())
    {
        merge_sort_(v, 0, v.size() - 1);
    }
}

#endif /* _MERGE_SORT_H_ */
