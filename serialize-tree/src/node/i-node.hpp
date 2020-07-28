#pragma once

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
