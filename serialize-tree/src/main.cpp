#include <tree/tree.hpp>
#include <parser/parser.hpp>

#include <iostream>


int main(int argc, char const* argv[])
{
    try
    {
        auto [in, out] = parser::cmd_line(argc, argv);

        Tree tree;
        tree.deserialize(in);
        tree.print();
        tree.serialize(out);
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
