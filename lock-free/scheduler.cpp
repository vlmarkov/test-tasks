#include "scheduler.hpp"

Scheduler::Scheduler(size_t thread_pool_size) : thread_pool_size_(thread_pool_size)
{
    for (size_t i = 0; i < thread_pool_size_; ++i) {
        thread_lock_free_list_.push_back(AlignedLockFreeList{
            .ptr = std::make_shared<LockFreeList>(),
            .cv = std::make_shared<std::condition_variable>(),
            .mtx = std::make_shared<std::mutex>()
        });
    }

    for (size_t i = 0; i < thread_pool_size_; ++i) {
        thread_pool_.emplace_back([&, tid = i](std::stop_token st) {
            run_worker_(st, tid);
        });
    }
}

void Scheduler::add_task(Task t) {
    static thread_local int tid = 0;

    thread_lock_free_list_[tid].ptr->push(std::move(t));
    {
        std::unique_lock<std::mutex> lock(*thread_lock_free_list_[tid].mtx.get());
        thread_lock_free_list_[tid].cv->notify_one();
    }

    // Simple Round-Robin to show task distribution
    tid++;
    tid = tid % thread_pool_size_;
}

void Scheduler::stop() {
    if (is_stop_)
        return;

    for (size_t i = 0; i < thread_pool_.size(); ++i) {
        thread_pool_[i].request_stop();
        {
            std::unique_lock<std::mutex> lock(*thread_lock_free_list_[i].mtx.get());
            thread_lock_free_list_[i].cv->notify_one();
        }
        thread_pool_[i].join();
    }

    is_stop_ = true;
}

void Scheduler::run_worker_(std::stop_token stop_token, size_t tid) {
    while (!stop_token.stop_requested()) {
        auto& lfl = thread_lock_free_list_[tid].ptr;
        auto& cv = thread_lock_free_list_[tid].cv;
        auto& mtx = thread_lock_free_list_[tid].mtx;

        if (lfl->empty() && !stop_token.stop_requested()) {
            std::unique_lock<std::mutex> lock(*mtx.get());
            // Preventing Lost Notifications:
            // If a notify call occurs before a thread enters the wait state but after it has checked the condition,
            // the notification might be "lost" if no predicate is used.
            // The predicate ensures that if the condition is already met when wait is called,
            // the thread doesn't block unnecessarily!
            cv->wait(lock, [&]() { return !lfl->empty() || stop_token.stop_requested(); });

            if (stop_token.stop_requested())
                return;
        }

        auto* head = thread_lock_free_list_[tid].ptr->pop_all();
        while (head != nullptr) {
            try {
                head->task.callback();
            } catch (...) {
                // TODO: some error handling!
            }

            auto* to_delete = head;
            head = head->next;

            delete to_delete;
        }
    }
}
