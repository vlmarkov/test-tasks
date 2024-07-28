#include <iostream>

#include <module_a/module_a.hpp>
#include <module_b/module_b.hpp>

int main() {
    std::cout << "module_a: " << module_a(13) << std::endl;
    std::cout << "module_b: " << module_b(5) << std::endl;

    return 0;
}
