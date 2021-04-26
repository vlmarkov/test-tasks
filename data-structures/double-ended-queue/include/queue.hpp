#ifndef _DOUBLE_ENDED_QUEUE_HPP_
#define _DOUBLE_ENDED_QUEUE_HPP_

#include <memory>


class DoubleEnededQueue
{
private:
    struct node
    {
        int value{0};
        node *next{nullptr};
        node *prev{nullptr};
    };

    node *front_{nullptr};
    node *back_{nullptr};
    std::size_t size_{0};

public:
    DoubleEnededQueue() = default;
    ~DoubleEnededQueue();

    void push_front(const int value);
    void push_back(const int value);
    int pop_front();
    int pop_back();
    int front() const;
    int back() const;
    void print() const;
    bool empty() const;
    std::size_t size() const;
};

#endif /* _DOUBLE_ENDED_QUEUE_HPP_ */
