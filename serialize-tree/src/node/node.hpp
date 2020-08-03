#pragma once

#include <node/i-node.hpp>

#include <vector>
#include <string>

namespace node
{

const char body_div   = ':';
const char body_start = '{';
const char body_end   = '}';
const char node_div   = ',';
const char node_empty[] = { body_start, body_end };

enum class type { integer, real, string };

}; // node

template <typename T>
class Node: public INode
{
    private:
        T value_;
        std::vector<u_inode_ptr> childs_;

    public:
        explicit Node(T value);
        ~Node() = default;

        void add_child(u_inode_ptr&& node) override;
        void serialize(std::ofstream& out) override;
        void debug() override;
        void print() override;
};
