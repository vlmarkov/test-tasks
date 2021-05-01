#include <binary-search.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    {
        std::vector<int> v{-16, 0, 3, 5, 15, 34, 77};
        std::cout << binary_search(v, -16) << std::endl;
    }

    {
        std::vector<int> v{-16, 0, 3, 5, 15, 34, 77};
        std::cout << binary_search(v, 5) << std::endl;
    }

    {
        std::vector<int> v{-16, 0, 3, 5, 15, 34, 77};
        std::cout << binary_search(v, 77) << std::endl;
    }

    {
        std::vector<int> v{-16, 0, 3, 5, 15, 34, 77};
        std::cout << binary_search(v, 99) << std::endl;
    }

    return 0;
}
