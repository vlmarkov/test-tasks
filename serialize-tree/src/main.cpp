#include <tree/tree.hpp>

#include <iostream>


int main(int argc, char const *argv[])
{
    // TODO: cmd-line arguments parsing
    // TODO: usage function

    try
    {
        Tree tree;
        tree.deserialize("./in_file.txt");
        tree.print();
        tree.serialize("./out_file.txt");
    }
    catch (std::string error)
    {
        std::cerr << error << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cerr << "unhandled exception" << std::endl;
        return -2;
    }

    return 0;
}
