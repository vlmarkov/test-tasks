#include <queue.hpp>


int main(int argc, char const *argv[])
{
    {
        DoubleEnededQueue deque;
        deque.print();

        deque.push_front(5);
        deque.print();
        deque.push_front(10);
        deque.print();
        deque.push_front(15);
        deque.print();

        deque.pop_front();
        deque.print();
    }

    {
        DoubleEnededQueue deque;
        deque.print();

        deque.push_back(5);
        deque.print();
        deque.push_back(10);
        deque.print();
        deque.push_back(15);
        deque.print();

        deque.pop_back();
        deque.print();
    }

   {
        DoubleEnededQueue deque;
        deque.print();

        deque.push_front(0);
        deque.print();
        deque.push_back(5);
        deque.print();
        deque.push_front(-5);
        deque.print();

        deque.pop_back();
        deque.print();

        deque.pop_front();
        deque.print();
    }

    return 0;
}
