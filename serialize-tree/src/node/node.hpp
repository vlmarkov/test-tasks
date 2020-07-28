#pragma once

#include <vector>
#include <string>
#include <memory>
#include <fstream>

class INode
{
    public:
        INode() = default;
        virtual ~INode() = default;

        virtual void add(std::unique_ptr<INode>& node) = 0;
        virtual void serialize(std::ofstream& out) = 0;

        virtual void debug() = 0;
        virtual void print() = 0;
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

        void add(std::unique_ptr<INode>& node);

        void serialize(std::ofstream& out);

        void debug();
        void print();
};

class Parser
{
    public:
        static std::unique_ptr<INode> deserialize(std::string& in);
};
