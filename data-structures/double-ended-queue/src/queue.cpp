#include <queue.hpp>

#include <iostream>


DoubleEnededQueue::~DoubleEnededQueue()
{
    while (!this->empty())
    {
        pop_front();
    }
}

void DoubleEnededQueue::push_front(const int value)
{
    auto new_node = new node();
    new_node->value = value;
    new_node->prev = nullptr;
    new_node->next = front_;

    if (new_node->prev)
    {
        new_node->next->prev = new_node;
    }
    if (!back_)
    {
        back_ = new_node;
    }

    front_ = new_node;
    size_++;
}

void DoubleEnededQueue::push_back(const int value)
{
    auto new_node = new node();
    new_node->value = value;
    new_node->next = nullptr;
    new_node->prev = back_;
    
    if (new_node->prev)
    {
        new_node->prev->next = new_node;
    }
    if (!front_)
    {
        front_ = new_node;
    }

    back_ = new_node;
    size_++;
}

int DoubleEnededQueue::pop_front()
{
    if (this->empty())
    {
        return -1;
    }

    auto to_delete = front_;

    front_ = front_->next;
    if (front_)
    {
        front_->prev = nullptr;
    }
    if (to_delete == back_)
    {
        back_ = nullptr;
    }

    to_delete->next = nullptr;
    to_delete->prev = nullptr;

    size_--;
    const auto rv = to_delete->value;
    delete to_delete;
    return rv;
}

int DoubleEnededQueue::pop_back()
{
    if (this->empty())
    {
        return -1;
    }

    auto to_delete = back_;

    back_ = back_->prev;
    if (back_)
    {
        back_->next = nullptr;
    }
    if (to_delete == front_)
    {
        front_ = nullptr;
    }

    to_delete->next = nullptr;
    to_delete->prev = nullptr;

    size_--;
    const auto rv = to_delete->value;
    delete to_delete;
    return rv;
}

int DoubleEnededQueue::front() const
{
    if (this->empty())
    {
        return -1;
    }

    return front_->value;
}

int DoubleEnededQueue::back() const
{
    if (this->empty())
    {
        return -1;
    }

    return back_->value;
}

void DoubleEnededQueue::print() const
{
    std::cout << "[DOUBLE ENDED QUEUE PRINT]: size : " << size_ << std::endl;
    for (auto it = front_; it != nullptr; it = it->next)
    {
        std::cout << "[DOUBLE ENDED QUEUE PRINT]: value[" << it->value << "]" << std::endl;
    }
}

bool DoubleEnededQueue::empty() const
{
    return size_ ? false : true;
}

std::size_t DoubleEnededQueue::size() const
{
    return size_;
}
