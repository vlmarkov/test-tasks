#include <node/node.hpp>

#include <iostream>
#include <typeinfo>
#include <tuple>

/*
 * Because of using separate class implementation
 * and by the task there are only three aviable types
 */
template class Node<int>;
template class Node<double>;
template class Node<std::string>;


template <class T>
void Node<T>::add(std::unique_ptr<INode>& node)
{
    this->childs_.emplace_back(std::move(node));
}

template <class T>
void Node<T>::serialize(std::ofstream& out)
{
    const auto size = this->childs_.size();
    const auto type_id = typeid(this->value_).name();

    if (std::string(type_id).compare("i") != 0 && std::string(type_id).compare("d") != 0) {
        out << "\"" << this->value_ << "\"" << ":{";
    } else {
        out << this->value_ << ":{";
    }
    for (size_t i = 0; i < size; ++i) {
        this->childs_[i]->serialize(out);
        if (i != size- 1) {
            out << ",";
        }
    }
    out << "}";
}

template <class T>
void Node<T>::print()
{
    const auto type_id = typeid(this->value_).name();

    if (std::string(type_id).compare("i") != 0 && std::string(type_id).compare("d") != 0) {
        std::cout << "\"" << this->value_ << "\"" << std::endl;
    } else {
        std::cout << this->value_ << std::endl;
    }

    for (auto& i : this->childs_) {
        i->print();
    }
}

template <class T>
void Node<T>::debug()
{
    std::cout << "Value : " << this->value_ << std::endl;
    std::cout << "Type  : " << typeid(this->value_).name() << std::endl;
    std::cout << "Childs: " << this->childs_.size() << std::endl;
    for (auto& i : this->childs_) {
        i->debug();
    }
}

std::tuple<int, std::string, std::string> parseNode(const std::string& in) 
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

    return std::make_tuple(type, value, std::string(in.c_str(), pos+1+2, std::string::npos-2));
}

std::unique_ptr<INode> createNode(int type, std::string value)
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

std::vector<INode> parseChilds(const std::string& str)
{
    std::vector<INode> childs;
/*
    //Count {[ and ]} until reach 0
    // after that check ,
    // if yes split it
    size_t pos = 0;
    auto brackets = 0;
    for (; pos < str.size(); )
    {
        pos = str.find("{[", pos);
        if (pos != std::string::npos)
        {
            brackets++;
        }
        pos = str.find("]}", pos);
        if (pos != std::string::npos)
        {
            brackets--;
        }
        if (brackets == 0)
        {
            // TODO: correct str move to body pos
            childs.emplace_back(Factory::deserialize(str)); // TODO
            pos += 2;
        }
    }
*/
    return childs;
}

bool is_valid(std::string& str)
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
        throw std::string("not vaild deserilze string");
    }

    auto [type, value, body] = parseNode(in);
    auto node = createNode(type, value);
    if (body.compare("{}") == 0)
    {
        return node;
    }
    /*
    for (auto child : parseChilds(body))
    {
        node.add(child);
    }
    */
/*
    std::unique_ptr<INode> bar = std::make_unique<Node<std::string>>(std::string("bar"));
    std::unique_ptr<INode> bar_c_d = std::make_unique<Node<double>>(2.015);
    std::unique_ptr<INode> bar_c_d_c_i  = std::make_unique<Node<int>>(9);
    std::unique_ptr<INode> bar_c_i = std::make_unique<Node<int>>(2015);
    std::unique_ptr<INode> bar_c_s = std::make_unique<Node<std::string>>(std::string("2015"));

    std::unique_ptr<INode> baz = std::make_unique<Node<std::string>>(std::string("baz"));
    std::unique_ptr<INode> baz_c_s = std::make_unique<Node<std::string>>(std::string("foo"));
    std::unique_ptr<INode> baz_c_d = std::make_unique<Node<double>>(6.28318);
    std::unique_ptr<INode> baz_c_d_c_s  = std::make_unique<Node<std::string>>(std::string("hello"));

    bar_c_d->add(bar_c_d_c_i);
    bar->add(bar_c_d);
    bar->add(bar_c_i);
    bar->add(bar_c_s);

    baz->add(baz_c_s);
    baz_c_d->add(baz_c_d_c_s);
    baz->add(baz_c_d);

    std::unique_ptr<INode> root = std::make_unique<Node<int>>(8);
    root->add(bar);
    root->add(baz);
*/
    return node;
}
