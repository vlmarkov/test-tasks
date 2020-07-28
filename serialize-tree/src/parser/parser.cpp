#include <parser/parser.hpp>

#include <iostream>
#include <tuple>


static std::tuple<int, std::string, std::string> parseNode(const std::string& in) 
{
    size_t pos = in.find(":");
    if (pos == std::string::npos)
    {
        throw std::string("malformed deserialize file");
    }

    auto value = std::string(in.c_str(), 0, pos);

    int type = 0; // int
    if (value.find("\"") != std::string::npos)
    {
        type = 2; // string
    }
    else if (value.find(".") != std::string::npos)
    {
        type = 1; // double
    }
    return std::make_tuple(type, value, std::string(in.c_str(), pos+1+1, in.size()-(pos+1+1)-1));
}

static std::unique_ptr<INode> createNode(int type, std::string value)
{
    std::unique_ptr<INode> root;
    switch (type)
    {
        case 0: // int
            root = std::make_unique<Node<int>>(std::stoi(value));
            break;
        case 1: // double
            root = std::make_unique<Node<double>>(std::stod(value));
            break;
        case 2: // string
            root = std::make_unique<Node<std::string>>(value);
            break;
    default:
        break;
    }
    return root;
}

static bool is_valid(std::string& str)
{
    auto brackets = 0;
    for (const auto& ch : str)
    {
        switch (ch)
        {
        case '{':
            brackets++;
            break;
        case '}':
            brackets--;
            break;
        default:
            break;
        }
    }
    return brackets ? false: true;
}

std::unique_ptr<INode> Parser::deserialize(std::string& in)
{
    if (!is_valid(in))
    {
        throw std::string("not valid deserialize string");
    }

    auto [type, value, body] = parseNode(in);
    auto node = createNode(type, value);
    if (body.compare("{}") == 0)
    {
        return node;
    }

    auto start_idx = 0;
    auto brackets = 0;
    for (size_t i = 0; i < body.size(); ++i)
    {
        switch (body[i])
        {
        case '{':
            brackets++;
            break;
        case '}':
            brackets--;
            if (brackets == 0)
            {
                auto child_str = std::string(body, start_idx, i+1);
                auto tmp =  Parser::deserialize(child_str);
                node->add(tmp);
                start_idx = i + 1 + 1;
            }
            break;
        default:
            break;
        }
    }

    return node;
}
