#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>


int main(int argc, char const* argv[])
{
    try
    {
        auto args = parser::cmd_line(argc, argv);

        Tree tree;
        tree.deserialize(args.first);
        tree.print();
        tree.serialize(args.second);
    }
    catch (Exception& e)
    {
        std::cerr << e.what() << " (" << e.code() << ")" << std::endl;
        return e.code();
    }
    catch (...)
    {
        std::cerr << "unhandled exception" << std::endl;
        return -1;
    }

    return 0;
}
