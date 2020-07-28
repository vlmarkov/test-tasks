#include <tree/tree.hpp>

#include <iostream>


void usage()
{
    std::cerr << "usage: serialize-tree -i [PATH_TO_INPUT] -o [PATH_TO_OUT]" << std::endl;
}

int main(int argc, char const *argv[])
{
    // TODO: cmd-line arguments parsing

    if (argc != 3)
    {
        usage();
        return -1;
    }

    try
    {
        Tree tree;
        tree.deserialize(argv[1]);
        tree.print();
        tree.serialize(argv[2]);
    }
    catch (std::string error)
    {
        std::cerr << error << std::endl;
        return -2;
    }
    catch (...)
    {
        std::cerr << "unhandled exception" << std::endl;
        return -3;
    }

    return 0;
}
