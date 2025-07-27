#include <gtest/gtest.h>

#include <thread>

#include "../lock_free_list.hpp"

TEST(LockFreeListTest, WithMultiplePushExpectValidTaskCounter) {
    auto counter = 0;
    LockFreeList lfl;

    std::thread t1 = std::thread([&](){
        for (auto i = 0; i < 1000; ++i) {
            lfl.push(Task());
        }
    });
    std::thread t2 = std::thread([&](){
        for (auto i = 0; i < 1000; ++i) {
            lfl.push(Task());
        }
    });


    {
        LockFreeList::Node* head = lfl.pop_all();
        while (head != nullptr) {
            LockFreeList::Node* next = head->next;
            delete head;
            head = next;

            ++counter;
        }
    }

    std::thread t3 = std::thread([&](){
        for (auto i = 0; i < 1000; ++i) {
            lfl.push(Task());
        }
    });

    t1.join();
    t2.join();
    t3.join();

    {
        LockFreeList::Node* head = lfl.pop_all();
        while (head != nullptr) {
            LockFreeList::Node* next = head->next;
            delete head;
            head = next;

            ++counter;
        }
    }

    EXPECT_EQ(counter, 3000);
}

TEST(LockFreeListTest, WithEmptyExpectEmpty) {
    LockFreeList lfl;

    EXPECT_TRUE(lfl.empty());
}


TEST(LockFreeListTest, WithOnePushExpectNonEmpty) {
    LockFreeList lfl;

    lfl.push(Task());
    EXPECT_FALSE(lfl.empty());
}
