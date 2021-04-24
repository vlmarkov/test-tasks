#include <linked-list.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    LinkedList ll;

    ll.print();

    ll.push_front(5);
    ll.print();

    ll.push_front(10);
    ll.print();

    ll.push_front(15);
    ll.print();

    std::cout << "linked_list_lookup: " << ll.lookup(15) << std::endl;
    std::cout << "linked_list_lookup: " << ll.lookup(25) << std::endl;

    ll.remove(15);
    std::cout << "linked_list_lookup: " << ll.lookup(15) << std::endl;
    ll.print();

    ll.pop_front();
    ll.print();

    return 0;
}
