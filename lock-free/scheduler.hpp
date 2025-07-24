#pragma once

#include "task.hpp"
#include "lock_free_list.hpp"

#include <new>
#include <thread>

struct AlignedLockFreeList
{
    alignas(std::hardware_destructive_interference_size) std::shared_ptr<LockFreeList> ptr;
};

class Scheduler {
public:
    Scheduler(size_t workers);

    void add_task(Task t);
    void stop();

private:
    const size_t workers_size_;
    std::jthread scheduler_;
    std::vector<std::jthread> thread_pool_;
    LockFreeList lock_free_list_;
    std::vector<AlignedLockFreeList> thread_lock_free_list_;

    void run_scheduler_(std::stop_token stop_token);
    void run_worker_(std::stop_token stop_token, size_t tid);
};
