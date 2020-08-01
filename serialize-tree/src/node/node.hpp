#pragma once

#include <node/i-node.hpp>

#include <vector>
#include <string>


#include <iostream>

template <typename T>
class Node: public INode
{
    private:
        T value_;
        std::vector<std::unique_ptr<INode>> childs_;

    public:
        explicit Node(T value) : value_(value) {}
        ~Node() = default;

        void add(std::unique_ptr<INode>& node);

        void serialize(std::ofstream& out);

        void debug();
        void print();
};
