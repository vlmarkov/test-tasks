#pragma once

#include <memory>
#include <fstream>


class INode;
typedef std::unique_ptr<INode> u_inode_ptr;

class INode
{
    public:
        INode() = default;
        virtual ~INode() = 0; // Denies creation (+ all functions are pure virtual)

        INode(const INode&)            = delete; // DOES
        INode(INode&&)                 = delete; // NOT
        INode& operator=(const INode&) = delete; // ALLOW
        INode& operator=(INode&&)      = delete; // ANY KIND OF COPY

        virtual void add_child(u_inode_ptr&& node) = 0;
        virtual void serialize(std::ofstream& out) noexcept = 0;

        virtual void debug() noexcept = 0;
        virtual void print() noexcept = 0;
};

INode::~INode()
{
    ;
}
