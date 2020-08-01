#pragma once

#include <node/i-node.hpp>

#include <vector>
#include <string>

namespace node
{
constexpr char body_div   = ':';
constexpr char body_start = '{';
constexpr char body_end   = '}';
constexpr char node_div   = ',';
constexpr char node_empty[] = { body_start, body_end };

enum class type { integer, real, string };
};

template <typename T>
class Node: public INode
{
    private:
        T value_;
        std::vector<std::unique_ptr<INode>> childs_;

    public:
        explicit Node(T value) : value_(value) {}
        ~Node() = default;

        void add_child(std::unique_ptr<INode>&& node);

        void serialize(std::ofstream& out);

        void debug();
        void print();
};
