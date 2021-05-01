#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

#include <vector>


int binary_search(std::vector<int>& v, const int key) // O(logn)
{
    int l = 0;
    int r = v.size() - 1;

    while (l <= r)
    {
        auto middle = (l + r) / 2;
        if (key == v[middle])
        {
            return key;
        }
        else if (key > v[middle])
        {
            l = middle + 1;
        }
        else
        {
            r = middle - 1;
        }
    }
    return -1;
}

#endif /* _BINARY_SEARCH_H_ */
