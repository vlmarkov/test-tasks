#pragma once

#include <chrono>
#include <functional>

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
using namespace std::literals::chrono_literals;

struct Task {
    std::function<void()>callback{};
    TimePoint when{};
};

struct TaskComparator {
    bool operator()(const Task& a, const Task& b) const {
        return a.when > b.when;
    }
};
