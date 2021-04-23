#include <stack.hpp>


int main(int argc, char const *argv[])
{
    Stack stack;

    stack.print();

    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    return 0;
}
