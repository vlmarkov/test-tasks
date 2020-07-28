#pragma once

#include <node/node.hpp>


class Tree
{
    public:
        explicit Tree();
        ~Tree();

        void serialize(const char* file);
        void deserialize(const char* file);
        void print();

    private:
        std::unique_ptr<INode> root_;
};
