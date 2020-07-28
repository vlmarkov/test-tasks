#pragma once

#include <node/node.hpp>


class Tree
{
    public:
        Tree() = default;
        ~Tree() = default;

        void deserialize(const char* in);
        void serialize(const char* out);
        void print();

    private:
        std::unique_ptr<INode> root_;
};
