#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>

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
    catch (Exception& e)
    {
        std::cerr << e.what() << std::endl;
        return e.code();
    }
    catch (...)
    {
        std::cerr << "unhandled exception" << std::endl;
        return -1;
    }

    return 0;
}
