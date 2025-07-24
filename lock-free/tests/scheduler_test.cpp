#include <gtest/gtest.h>

#include <thread>

#include "../scheduler.hpp"

TEST(SchedulerTest, WithSomeWorkers) {
    Scheduler scheduler(8);

    std::thread t1 = std::thread([&](){
        for (auto i = 0; i < 10; ++i) {
            scheduler.add_task(Task{.callback = [](){}});
        }
    });

    t1.join();
    scheduler.stop();
}
