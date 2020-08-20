#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>
#include <fstream>
#include <cerrno>


/*
 * deserialize - deserializes file content to the Tree
 */
void Tree::deserialize(const std::string& filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    if (!ifs.is_open())
    {
        throw Exception("can't open deserialize file", errno);
    }

    std::string line;
    std::getline(ifs, line);
    ifs.close();

    if (line.size() == 0)
    {
        return; // An empty file
    }

    if (root_ != nullptr)
    {
        root_.reset();
    }

    if (!parser::check_deserialize(line))
    {
        throw Exception("malformed deserialize string", static_cast<int>(errors::malformed));
    }

    root_ = parser::deserialize(line);
}

/*
 * serialize - serializes Tree content to the file
 */
void Tree::serialize(const std::string& filename)
{
    if (root_ == nullptr)
    {
        return;
    }

    std::ofstream ofs(filename, std::ofstream::out);
    if (!ofs.is_open())
    {
        throw Exception("can't open serialize file", errno);
    }

    root_->serialize(ofs);
    ofs.close();
}

/*
 * print - prints Tree to standard out if it contains any Nodes
 */
void Tree::print() noexcept
{
    if (root_ != nullptr)
    {
        root_->print();
    }
}