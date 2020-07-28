#pragma once

#include <node/node.hpp>


class Parser
{
    public:
        static std::unique_ptr<INode> deserialize(std::string& in);
};
