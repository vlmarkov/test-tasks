#pragma once

#include <node/node.hpp>


namespace parser
{
    std::tuple<const char*, const char*> cmd_line(int argc, char const *argv[]);
    u_inode_ptr deserialize(std::string& str);
    bool check_deserialize(const std::string& str);
};
