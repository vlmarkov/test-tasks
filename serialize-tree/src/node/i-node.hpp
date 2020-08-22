#pragma once

#include <memory>
#include <fstream>


class INode;
typedef std::unique_ptr<INode> u_inode_ptr;

class INode
{
    public:
        INode() = default;
        virtual ~INode() = default;

        INode(const INode&) = delete;             // DOES
        INode(const INode&&) = delete;            // NOT
        INode& operator=(const INode&) = delete;  // ALLOW
        INode& operator=(const INode&&) = delete; // ANY KIND OF COPY

        // Provides different type of child node adding interface
        virtual void add_child(u_inode_ptr& node) = 0; // not in use
        virtual void add_child(u_inode_ptr&& node) = 0;

        virtual void serialize(std::ofstream& out) noexcept = 0;

        virtual void debug() noexcept = 0;
        virtual void print() noexcept = 0;
};
