#include <tree/tree.hpp>

#include <iostream>
#include <fstream>


Tree::Tree()
{

}

Tree::~Tree()
{

}

void Tree::serialize(const char* file)
{
    if (file == nullptr)
    {
        throw std::string("serialize file null");
    }

    std::ofstream out(file, std::ofstream::out);
    if (!out.is_open())
    {
        throw std::string("can't open serialize file");
    }

    this->root_->serialize(out);
    out.close();
}

void Tree::deserialize(const char* file)
{
    if (file == nullptr)
    {
        throw std::string("deserialize file null");
    }

    std::ifstream in(file, std::ifstream::in);
    if (!in.is_open())
    {
        throw std::string("can't open deserialize file");
    }

    std::string line;
    std::getline(in, line);
    in.close();

    this->root_ = Factory::deserialize(line); // TODO: node::deserialize!
}

void Tree::print()
{
    this->root_->print();
}