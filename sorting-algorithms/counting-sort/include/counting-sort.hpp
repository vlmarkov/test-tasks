#ifndef _COUNTING_SORT_H_
#define _COUNTING_SORT_H_

#include <vector>
#include <array>

void counting_sort(std::vector<int>& v) // O(n+k)
{
    auto max = 0;
    for (auto& i : v)
    {
        if (i < 0)
        {
            throw "doesn't support negative values!";
        }

        if (i > max)
        {
            max = i;
        }
    }

    std::vector<int> counting(max + 1);

    for (auto& i : v)
    {
        counting[i]++;
    }

    auto cnt = 0;
    for (std::size_t i = 0; i < counting.size(); ++i)
    {
        for (auto j = 0; j < counting[i]; ++j)
        {
            v[cnt++] = i;
        }
    }
}

#endif /* _COUNTING_SORT_H_ */
