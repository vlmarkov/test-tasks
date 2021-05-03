#include <binary-search-tree.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    BinarySearchTree bst;

    std::cout << "add(50)    : " << bst.add(50, "50") << std::endl;
    std::cout << "add(50)    : " << bst.add(40, "40") << std::endl;
    std::cout << "add(50)    : " << bst.add(60, "60") << std::endl;
    std::cout << "add(50)    : " << bst.add(10, "10") << std::endl;
    std::cout << "lookup(50) : " << bst.lookup(50) << std::endl;
    std::cout << "delete(50) : " << bst.remove(50) << std::endl;
    std::cout << "lookup(50) : " << bst.lookup(50) << std::endl;
    std::cout << "delete(50) : " << bst.remove(50) << std::endl;
    std::cout << "size()     : " << bst.size() << std::endl;
    std::cout << "empty()    : " << bst.empty() << std::endl;
    bst.print_inorder();

    return 0;
}
