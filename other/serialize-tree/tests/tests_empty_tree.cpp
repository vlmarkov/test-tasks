#include "tests.hpp"


int test_empty_tree()
{
    try
    {
        TestWriter tw("./in.txt", "");
        TestWriter tr("./out.txt", "");

        Tree tree;
        tree.deserialize("./in.txt");
        tree.serialize("./out.txt");
    }
    catch (...)
    {
        return -1;
    }

    return 0; 
}

int main(int argc, char const* argv[])
{
    if (test_empty_tree() != 0)
    {
        return -1;
    }
    return 0;
}
