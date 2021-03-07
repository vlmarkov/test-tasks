#include <smart-pointer.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    {
        SmartPointer<int> sp0(new int);
        SmartPointer<int> sp(new int);
        SmartPointer<int> sp1 = sp;
        *sp1.get() = 5;
        std::cout << *sp.get() << std::endl;
        sp1 = sp0;
    }

    {
        SmartPointer<int[]> sp0(new int[10]);
        SmartPointer<int[]> sp(new int[20]);
        SmartPointer<int[]> sp1 = sp;
        *sp1.get() = 5;
        std::cout << *sp.get() << std::endl;
        sp1 = sp0;
    }
    return 0;
}
