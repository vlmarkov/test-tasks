#pragma once

#include <memory>
#include <fstream>


class INode;
typedef std::unique_ptr<INode> u_inode_ptr;

class INode
{
    public:
        virtual ~INode() = default;

        virtual void add_child(u_inode_ptr&& node) = 0;
        virtual void serialize(std::ofstream& out) = 0;
        virtual void debug() = 0;
        virtual void print() = 0;
};
