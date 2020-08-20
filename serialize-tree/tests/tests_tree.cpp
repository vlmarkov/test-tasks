#include "tests.hpp"


int test_tree(const char* sample)
{
    try
    {
        const 
        TestWriter tw("./in.txt", sample);
        TestWriter tr("./out.txt", "");

        Tree tree;
        tree.deserialize("./in.txt");
        tree.serialize("./out.txt");

        if (compare("./out.txt", sample) != 0)
        {
            return -1;
        }
    }
    catch (...)
    {
        return -1;
    }

    return 0; 
}

int main(int argc, char const* argv[])
{
    if (test_tree("8:{}") != 0)
    {
        return -1;
    }
    if (test_tree("8:{\"bar\":{2.015:{9:{}},2015:{},\"2015\":{}},\"baz\":{\"foo\":{},6.28318:{\"hello\":{}}}}") != 0)
    {
        return -1;
    }
    if (test_tree("8:") == 0)
    {
        return -1;
    }
    return 0;
}
