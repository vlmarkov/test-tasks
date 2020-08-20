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

        Tree(const Tree&) = delete;             // DOES
        Tree(const Tree&&) = delete;            // NOT
        Tree& operator=(const Tree&) = delete;  // ALLOW
        Tree& operator=(const Tree&&) = delete; // ANY KIND OF COPY

        void deserialize(const std::string& filename);
        void serialize(const std::string& filename);
        void print() noexcept;

    private:
        std::unique_ptr<INode> root_;
};
