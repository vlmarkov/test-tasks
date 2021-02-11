#include <quick-sort.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{

    std::vector<int> v{5, 0, 3, 77, 15, -16, 34};
    quick_sort(v);

    for (auto& i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
