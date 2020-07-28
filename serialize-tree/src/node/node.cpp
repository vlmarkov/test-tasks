#include <node/node.hpp>

#include <iostream>
#include <typeinfo>


/*
 * Because of using template class implementation:
 * also the task description points to use int, double, string
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

    out << this->value_ << ":{";
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
    std::cout << this->value_ << std::endl;
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
