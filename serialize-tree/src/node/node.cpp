#include <node/node.hpp>

#include <iostream>
#include <typeinfo>


/*
 * Because of template class implementation
 */
template class Node<int>;
template class Node<double>;
template class Node<std::string>;

template <class T>
Node<T>::Node(T value) : value_(value)
{
    ;
}

template <class T>
void Node<T>::add_child(u_inode_ptr&& node) noexcept
{
    childs_.emplace_back(std::move(node));
}

template <class T>
void Node<T>::serialize(std::ofstream& out) noexcept
{
    out << value_ << node::body_div << node::body_start;
    for (auto it = childs_.begin(); it != childs_.end(); ++it)
    {
        (*it)->serialize(out);
        if (it != childs_.end() - 1)
        {
            out << node::node_div;
        }
    }
    out << node::body_end;
}

template <class T>
void Node<T>::print() noexcept
{
    std::cout << value_ << std::endl;
    for (const auto& i : childs_)
    {
        i->print();
    }
}

template <class T>
void Node<T>::debug() noexcept
{
    std::cout << "Value  : " << value_ << std::endl;
    std::cout << "Type   : " << typeid(value_).name() << std::endl;
    std::cout << "Childs : " << childs_.size() << std::endl;
    for (const auto& i : childs_)
    {
        i->debug();
    }
}
