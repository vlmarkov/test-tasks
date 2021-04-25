#ifndef _STACK_HPP_
#define _STACK_HPP_

#include <memory>


class Stack
{
private:
    struct node
    {
        node(int value, std::unique_ptr<node>&& next);
        int value{0};
        std::unique_ptr<node> next{nullptr};
    };

    std::unique_ptr<node> head_{nullptr};
    std::size_t size_{0};

public:
    Stack() = default;
    ~Stack() = default;

    void push(const int value);
    int pop();
    int top() const; 
    std::size_t size() const;
    bool empty() const;
    void print() const;
};

#endif /* _STACK_HPP_ */
