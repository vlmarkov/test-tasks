#pragma once

#include <memory>
#include <fstream>

class INode
{
    public:
        virtual ~INode() = default;

        virtual void add_child(std::unique_ptr<INode>&& node) = 0;

        virtual void serialize(std::ofstream& out) = 0;

        virtual void debug() = 0;
        virtual void print() = 0;
};
