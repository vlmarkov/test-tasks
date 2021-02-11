#include <ring-buffer.hpp>

#include <iostream>
#include <string>
#include <vector>

class MyClass
{

};

int main(int argc, char const *argv[])
{
    {
        RingBuffer<MyClass, 10> ring_buffer;
        ring_buffer.push({});
        //std::cout << ring_buffer << std::endl;
    }

    {
        RingBuffer<std::string, 10> ring_buffer;
        ring_buffer.push({"test"});
        std::cout << ring_buffer << std::endl;
    }

    {
        RingBuffer<std::vector<int>, 10> ring_buffer;
        ring_buffer.push({});
        //std::cout << ring_buffer << std::endl;
    }

    RingBuffer<int, 10> ring_buffer;
    ring_buffer.push(5);
    ring_buffer.push(6);
    //ring_buffer.clear();

    std::cout << ring_buffer.size() << std::endl;
    std::cout << ring_buffer.pop() << std::endl;
    std::cout << ring_buffer << std::endl;
    return 0;
}
