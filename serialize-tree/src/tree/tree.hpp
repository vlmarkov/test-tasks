#pragma once

#include <node/node.hpp>

/*
 * For more Tree structure details see feadme file
 */
class Tree
{
    public:
        Tree() = default;
        ~Tree() = default;

        void deserialize(const char* file);
        void serialize(const char* file);
        void print();

    private:
        std::unique_ptr<INode> root_;
};
