#include <parser/parser.hpp>
#include <exception/exception.hpp>

#include <iostream>
#include <tuple>

#include <string.h>


static auto new_node_(node::type t, std::string v) -> std::unique_ptr<INode>
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
    throw Exception("unknown Node type");
}

static auto deserialize_node_(const std::string& in) -> std::tuple<node::type, std::string, std::string>
{
    size_t pos = in.find(node::body_div);
    if (pos == std::string::npos)
    {
        throw Exception("malformed deserialize file");
    }

    auto value = std::string(in.c_str(), 0, pos);

    auto type = node::type::integer;
    // TODO: dosen't allow special symbols inside Node value
    if (value.find("\"") != std::string::npos)
    {
        type = node::type::string;
    }
    else if (value.find(".") != std::string::npos)
    {
        type = node::type::real;
    }

    const auto start = pos + sizeof(node::body_div) + sizeof(node::body_start);
    const auto end = in.size() - start - 1;

    return std::make_tuple(type, value, std::string(in.c_str(), start, end));
}

namespace parser
{

std::tuple<const char*, const char*> cmd_line(int argc, char const *argv[])
{
    if (argc != 5)
    {
        throw Exception("usage: serialize-tree -i [PATH_TO_INPUT] -o [PATH_TO_OUT]");
    }
    if (::strcmp(argv[1], "-i") != 0)
    {
        throw Exception("usage: serialize-tree -i [PATH_TO_INPUT] -o [PATH_TO_OUT]");
    }
    if (::strcmp(argv[3], "-o") != 0)
    {
        throw Exception("usage: serialize-tree -i [PATH_TO_INPUT] -o [PATH_TO_OUT]");
    }

    return std::make_tuple(argv[2], argv[4]);
}


std::unique_ptr<INode> deserialize(std::string& str)
{
    auto [type, value, body] = deserialize_node_(str);
    auto node = new_node_(type, value);
    if (body.compare(node::node_empty) == 0)
    {
        return node;
    }

    auto start_idx = 0;
    auto brackets = 0;
    for (size_t i = 0; i < body.size(); ++i)
    {
        switch (body[i])
        {
            case node::body_start:
                brackets++;
                break;
            case node::body_end:
                brackets--;
                if (brackets == 0)
                {
                    const auto indent = i + sizeof(node::body_end);
                    auto child_str = std::string(body, start_idx, indent);
                    node->add_child(parser::deserialize(child_str));
                    start_idx = indent + sizeof(node::node_div);
                }
                break;
        }
    }

    return node;
}

/*
 * Very simple cheker, without additional logic
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