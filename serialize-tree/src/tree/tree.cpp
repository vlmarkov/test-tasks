#include <tree/tree.hpp>
#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>
#include <fstream>

/*
 * deserialize - deserializes file content to the Tree
 */
void Tree::deserialize(const char* file)
{
    if (file == nullptr)
    {
        throw Exception("deserialize file is null");
    }

    std::ifstream ifs(file, std::ifstream::in);
    if (!ifs.is_open())
    {
        throw Exception("can't open deserialize file");
    }

    std::string line;
    std::getline(ifs, line);
    ifs.close();

    if (this->root_ != nullptr)
    {
        this->root_.reset();
    }

    if (!parser::check_deserialize(line))
    {
        throw Exception("malformed deserialize string");
    }

    this->root_ = parser::deserialize(line);
}

/*
 * serialize - serializes Tree content to the file
 */
void Tree::serialize(const char* file)
{
    if (this->root_ == nullptr)
    {
        return;
    }

    if (file == nullptr)
    {
        throw Exception("serialize file is null");
    }

    std::ofstream ofs(file, std::ofstream::out);
    if (!ofs.is_open())
    {
        throw Exception("can't open serialize file");
    }

    this->root_->serialize(ofs);
    ofs.close();
}

/*
 * print - prints Tree to standard out if it contains any Nodes
 */
void Tree::print()
{
    if (this->root_ != nullptr)
    {
        this->root_->print();
    }
}