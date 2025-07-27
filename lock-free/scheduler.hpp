#pragma once

#include "task.hpp"
#include "lock_free_list.hpp"

#include <new>
#include <thread>
#include <memory>
#include <condition_variable>

struct alignas(std::hardware_destructive_interference_size) AlignedLockFreeList
{
    // Avoids false-sharing
    std::shared_ptr<LockFreeList> ptr;
    std::shared_ptr<std::condition_variable> cv;
    std::shared_ptr<std::mutex> mtx;
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
