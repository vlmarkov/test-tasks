#pragma once

#include "task.hpp"

#include <atomic>

class LockFreeList {
public:
    struct Node {
        Task task{};
        std::atomic<Node*> next{nullptr};
    };

    void push(Task t);
    Node* pop_all();
    bool empty() const;

private:
    std::atomic<Node*> head_{nullptr};
};
