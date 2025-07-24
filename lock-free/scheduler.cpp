#include "scheduler.hpp"

Scheduler::Scheduler(size_t workers) : workers_size_(workers)
{
    thread_lock_free_list_.resize(workers_size_, AlignedLockFreeList{std::make_shared<LockFreeList>()});

    scheduler_ = std::jthread([&](std::stop_token st) {
        run_scheduler_(st);
    });

    for (size_t i = 0; i < workers_size_; ++i) {
        thread_pool_.emplace_back([&, tid = i](std::stop_token st) {
            run_worker_(st, tid); 
        });
    }
}

void Scheduler::add_task(Task t) {
    lock_free_list_.push(std::move(t));
}

void Scheduler::stop() {
    if (!scheduler_.joinable())
        return;

    scheduler_.request_stop();
    scheduler_.join(); 

    for (auto& t : thread_pool_) {
        t.request_stop();
        t.join();            
    }
}

void Scheduler::run_scheduler_(std::stop_token stop_token) {
    size_t tid = 0;

    while (!stop_token.stop_requested()) {
        auto* head = lock_free_list_.pop_all();

        while (head != nullptr) {
            thread_lock_free_list_[tid].ptr->push(head->task);
            tid = (++tid % workers_size_);

            auto* to_delete = head;
            head = head->next;

            delete to_delete;
        }

        std::this_thread::sleep_for(1s);
    }
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
