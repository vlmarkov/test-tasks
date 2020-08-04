#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>
#include <tuple>

#include <string.h>


static u_inode_ptr new_node_(node::type t, std::string v)
{
    switch (t)
    {
        case node::type::integer:
            return std::make_unique<Node<int>>(std::stoi(v));
        case node::type::real:
            return std::make_unique<Node<double>>(std::stod(v));
        case node::type::string:
            return std::make_unique<Node<std::string>>(v);
    }
    throw Exception("unknown Node type", static_cast<int>(errors::type));
}

static auto deserialize_node_(const std::string& str)
{
    // TODO: support ignoring special symbols inside Node value
    size_t pos = str.find(node::body_div);
    if (pos == std::string::npos)
    {
        throw Exception("malformed deserialize file", static_cast<int>(errors::malformed));
    }

    auto value = std::string(str.c_str(), 0, pos);

    auto type = node::type::integer;
    // TODO: does not allow special symbols inside Node value
    if (value.find("\"") != std::string::npos)
    {
        type = node::type::string;
    }
    else if (value.find(".") != std::string::npos)
    {
        type = node::type::real;
    }

    const auto start = pos + sizeof(node::body_div) + sizeof(node::body_start);
    const auto end = str.size() - start - 1;

    return std::make_tuple(type, value, std::string(str.c_str(), start, end));
}

namespace parser
{

std::pair<std::string, std::string> cmd_line(int argc, char const* argv[])
{
    const char* usage = "usage: serialize-tree -i [PATH_TO_INPUT] -o [PATH_TO_OUT]";

    if (argc != 5)
    {
        throw Exception(usage, static_cast<int>(errors::cmdline));
    }
    if (::strcmp(argv[1], "-i") != 0)
    {
        throw Exception(usage, static_cast<int>(errors::cmdline));
    }
    if (::strcmp(argv[3], "-o") != 0)
    {
        throw Exception(usage, static_cast<int>(errors::cmdline));
    }

    return std::make_pair(std::string(argv[2]), std::string(argv[4]));
}

/*
 * deserialize - converts string into Tree structure
 */
u_inode_ptr deserialize(std::string& str)
{
    auto [type, value, body] = deserialize_node_(str);
    auto node = new_node_(type, value);
    if (body.compare(node::node_empty) == 0)
    {
        return node;
    }

    auto start_it = body.begin();
    auto brackets = 0;
    for (auto it = body.begin(); it != body.end(); ++it)
    {
        // TODO: instead of each time finds Node's borders
        //       we could go through and create Nodes on fly
        //       in order to reduce algorithm complexity
        //       but we need to maintain Node's relationship
        switch (*it)
        {
            case node::body_start:
                brackets++;
                break;
            case node::body_end:
                brackets--;
                if (brackets == 0)
                {
                    auto end_it = it + sizeof(node::body_start);
                    auto child_str = std::string(start_it, end_it);
                    node->add_child(parser::deserialize(child_str));
                    start_it = end_it + sizeof(node::node_div);
                }
                break;
        }
    }

    return node;
}

/*
 * Very simple checker, without additional logic
 */
bool check_deserialize(const std::string& str)
{
    auto brackets = 0;
    for (const auto& ch : str)
    {
        switch (ch)
        {
            case node::body_start: brackets++; break;
            case node::body_end: brackets--; break;
        }
    }

    return brackets ? false: true;
}

}; // parser
