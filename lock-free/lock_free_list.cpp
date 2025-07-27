#include "lock_free_list.hpp"

void LockFreeList::push(Task t) {
    Node* current_head = nullptr;
    auto* new_head = new Node();
    new_head->task = std::move(t);

    do {
        // The acquire operation ensures that any writes performed before
        // the corresponding release operation are visible to the thread performing the acquire.
        // This creates a synchronization point between the two threads. 
        current_head = head_.load(std::memory_order_acquire);
        new_head->next.store(current_head, std::memory_order_release);

    // It compares the value of an atomic variable with an expected value,
    // and if they are equal,
    // replaces the atomic variable's value with a desired value
    } while (!head_.compare_exchange_weak(current_head, new_head,
                                          std::memory_order_release,
                                          std::memory_order_relaxed));
    // memory_order_release ensures that all memory writes performed before this atomic operation
    // in the current thread become visible to other threads that perform
    // a corresponding memory_order_acquire load on the same atomic variable
}

LockFreeList::Node* LockFreeList::pop_all() {
    // memory_order_acq_rel guarantees that if one thread performs
    // a store with memory_order_release/memory_order_acq_rel
    // and another thread performs
    // a load with memory_order_acquire/memory_order_acq_rel)
    // on the same atomic variable, then all writes performed before
    // the release are visible to the thread performing the acquire

    // exchange it atomically reads the current value of an atomic variable,
    // replaces it with a new value, and returns the old value
    // that was previously held
    return head_.exchange(nullptr, std::memory_order_acq_rel);
}

bool LockFreeList::empty() const {
    return head_.load() == nullptr;
}
