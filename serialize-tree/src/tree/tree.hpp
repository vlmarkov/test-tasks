#pragma once

#include <node/node.hpp>

/*
 * For more Tree structure details see readme file
 */
class Tree
{
    public:
        Tree() = default;
        ~Tree() = default;

        Tree(const Tree&) = delete;             // Does
        Tree(const Tree&&) = delete;            // not
        Tree& operator=(const Tree&) = delete;  // allow
        Tree& operator=(const Tree&&) = delete; // any kind of copy

        void deserialize(const char* file);
        void serialize(const char* file);
        void print();

    private:
        std::unique_ptr<INode> root_;
};
