#pragma once

#include "task.hpp"
#include "lock_free_list.hpp"

#include <new>
#include <thread>
#include <memory>

struct alignas(std::hardware_destructive_interference_size) AlignedLockFreeList
{
    // Avoids false-sharing
    std::shared_ptr<LockFreeList> ptr;
};

class Scheduler {
public:
    Scheduler(size_t thread_pool_size);

    void add_task(Task t);
    void stop();

private:
    bool is_stop_{false};
    const size_t thread_pool_size_;
    std::vector<std::jthread> thread_pool_;
    std::vector<AlignedLockFreeList> thread_lock_free_list_;

    void run_worker_(std::stop_token stop_token, size_t tid);
};
