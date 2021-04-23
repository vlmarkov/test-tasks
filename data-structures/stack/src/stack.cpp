#include <stack.hpp>

#include <iostream>


Stack::Stack()
{
    ;
}

Stack::~Stack()
{
    ;
}

void Stack::push(const int value)
{
    auto new_node = std::make_unique<node>();
    
    new_node->value = value;
    new_node->next = std::move(head_);
    
    head_ = std::move(new_node);

    size_++;

    return;
}

int Stack::pop()
{
    if (this->empty())
    {
        return -1;
    }

    auto node = std::move(head_);
    
    head_ = std::move(node->next);
    node->next.reset();

    size_--;

    return node->value;
}

int Stack::top() const
{
    if (this->empty())
    {
        return -1;
    }

    return head_->value;
}

std::size_t Stack::size() const
{
    return size_;
}

bool Stack::empty() const
{
    return size_ > 0 ? false : true;
}

void Stack::print() const
{
    std::cout << "[STACK PRINT]: size : " << size_ << std::endl;

    for (auto it = head_.get(); it != nullptr; it = it->next.get())
    {
        std::cout << "[STACK PRINT]: value[" << it->value << "]" << std::endl;
    }
}
