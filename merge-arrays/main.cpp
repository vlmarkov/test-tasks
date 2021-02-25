#include <unordered_set>
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> merge_array(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.empty() && b.empty())
    {
        return {};
    }

    std::size_t a_idx = 0;
    std::size_t b_idx = 0;

    std::vector<T> c(a.size() + b.size(), {});

    for (std::size_t i = 0; i < c.size(); ++i)
    {
        if (a[a_idx] > b[b_idx])
        {
            if (b_idx + 1 <= b.size())
            {
                c[i] = b[b_idx++];
            }
            else
            {
                c[i] = a[a_idx++];   
            }
        }
        else
        {
            if (a_idx + 1 <= a.size())
            {
                c[i] = a[a_idx++];
            }
            else
            {
                c[i] = b[b_idx++];
            }
        }
    }
    
    return c;
}

template <typename T>
std::vector<T> merge_array_v2(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.empty() && b.empty())
    {
        return {};
    }

    std::size_t a_idx = 0;
    std::size_t b_idx = 0;
    std::size_t c_idx = 0;

    std::vector<T> c(a.size() + b.size(), {});

    while (b_idx < b.size() && a_idx < a.size())
    {
        if (a[a_idx] > b[b_idx])
        {
            c[c_idx++] = b[b_idx++];
        }
        else
        {
            c[c_idx++] = a[a_idx++];
        }
    }

    while (b_idx < b.size())
    {
        c[c_idx++] = b[b_idx++];
    }

    while (a_idx < a.size())
    {
        c[c_idx++] = a[a_idx++];
    }

    return c;
}

template <typename T>
std::vector<T> merge_array_v3(const std::vector<T>& a, const std::vector<T>& b)
{
    if (a.empty() && b.empty())
    {
        return {};
    }

    if (a.empty() || b.empty())
    {
        return {};
    }

    std::unordered_set<T> set;
    std::vector<T> c;

    for (auto i : a)
    {
        // TODO: do not forget about uniqueness
        set.insert(i);
    }

    for (auto i : b)
    {
        if (set.find(i) != set.end())
        {
            c.push_back(i);
        }
    }

    return c;
}

int main(int argc, char const *argv[])
{
    std::vector<int> a{1, 2, 6, 36, 89, 136};
    std::vector<int> b{0, 3, 7, 17, 44, 55, 138};

    for (auto i : merge_array(a, b))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto i : merge_array_v2(a, b))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::vector<int> a1{0, 2, 6, 17, 89, 136};
    std::vector<int> b1{0, 3, 7, 17, 44, 55, 89};

    for (auto i : merge_array_v3(a1, b1))
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
