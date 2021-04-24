#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include <memory>


class LinkedList
{
private:
    struct node
    {
        int value{0};
        std::unique_ptr<node> next{nullptr};
    };

    std::size_t size_{0};
    std::unique_ptr<node> head_{nullptr};

public:
    LinkedList() = default;
    ~LinkedList() = default;

    void push_front(const int value);
    int pop_front();
    bool remove(const int value);
    bool lookup(const int value) const;
    void print() const;
    bool empty() const;
    std::size_t size() const;
};

#endif /* _LINKED_LIST_HPP_ */
