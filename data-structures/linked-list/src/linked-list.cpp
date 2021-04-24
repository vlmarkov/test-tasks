#include <linked-list.hpp>

#include <iostream>


void LinkedList::push_front(const int value)
{
    auto new_node = std::make_unique<node>();

    new_node->value = value;
    new_node->next = std::move(head_);

    head_ = std::move(new_node);    
    size_++;
}

int LinkedList::pop_front()
{
    if (this->empty())
    {
        return -1;
    }

    auto node = std::move(head_);
    
    head_ = std::move(node->next);
    size_--;

    return node->value;
}

bool LinkedList::remove(const int value)
{
    node *prev = nullptr;
    for (auto it = head_.get(); it != nullptr; it = it->next.get())
    {
        if (it->value == value)
        {
            if (it == head_.get())
            {
                head_ = std::move(it->next);
            }
            else
            {
                auto next = std::move(it->next);
                auto to_delete = std::move(prev->next);
                prev->next = std::move(next);
            }
            size_--;
            return true;
        }
        prev = it;
    }
    return false;
}

bool LinkedList::lookup(const int value) const
{
    for (auto it = head_.get(); it != nullptr; it = it->next.get())
    {
        if (it->value == value)
        {
            return true;
        }
    }
    return false;
}

void LinkedList::print() const
{
    std::cout << "[LINKED LIST PRINT]: size : " << size_ << std::endl;
    for (auto it = head_.get(); it != nullptr; it = it->next.get())
    {
        std::cout << "[LINKED LIST PRINT]: value[" << it->value << "]" << std::endl;
    }
}

bool LinkedList::empty() const
{
    return size_ > 0 ? false : true;
}

std::size_t LinkedList::size() const
{
    return size_;
}
