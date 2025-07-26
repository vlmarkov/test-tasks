#include <gtest/gtest.h>

#include "../scheduler.hpp"

TEST(SchedulerTest, WithOneCallbackCallExpectSuccessOnCallbackCall) {
    Scheduler scheduler(8);

    std::mutex m;
    std::condition_variable cv;
    bool done = false;

    auto callback = [&]() {
        std::unique_lock lk(m);
        done = true;
        cv.notify_one();
    };

    scheduler.add_task(Task{.callback = callback});

    {
        std::unique_lock lk(m);
        cv.wait(lk, [&](){ return done; });
        EXPECT_TRUE(done);
    }

    scheduler.stop();
}
