#include "scheduler.hpp"

Scheduler::Scheduler(size_t thread_pool_size) : thread_pool_size_(thread_pool_size)
{
    thread_lock_free_list_.resize(thread_pool_size_, AlignedLockFreeList{std::make_shared<LockFreeList>()});

    for (size_t i = 0; i < thread_pool_size_; ++i) {
        thread_pool_.emplace_back([&, tid = i](std::stop_token st) {
            run_worker_(st, tid); 
        });
    }
}

void Scheduler::add_task(Task t) {
    static thread_local int tid = 0;

    thread_lock_free_list_[tid].ptr->push(std::move(t));

    // Simple Round-Robin to show task distribution
    tid++;
    tid = tid % thread_pool_size_;
}

void Scheduler::stop() {
    if (is_stop_)
        return;

    for (auto& t : thread_pool_) {
        t.request_stop();
        t.join();
    }

    is_stop_ = true;
}

void Scheduler::run_worker_(std::stop_token stop_token, size_t tid) {
    while (!stop_token.stop_requested()) {
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

        std::this_thread::sleep_for(1s);
    }
}
