#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <string>
#include <queue>
#include <atomic>

struct Task {
    std::string data{"placehoder for data"};
};

class ThreadSafeQueue {
    private:
        std::queue<Task> queue_;
        std::unique_ptr<std::mutex> mutex_;

    public:
        ThreadSafeQueue(): mutex_(std::make_unique<std::mutex>()) {}

        ThreadSafeQueue(const ThreadSafeQueue& rhs) = delete;
        ThreadSafeQueue& operator=(const ThreadSafeQueue& rhs) = delete;

        void Push(const Task& task) {
            auto *raw_mutex_ptr = mutex_.get();
            std::lock_guard<std::mutex> lock(*raw_mutex_ptr);

            queue_.push(task);
        }

        Task Pop() {
            auto *raw_mutex_ptr = mutex_.get();
            std::lock_guard<std::mutex> lock(*raw_mutex_ptr);

            if (queue_.empty()) {
                return {}; // TODO: do I need this behavior?
            }

            auto t = queue_.front();
            queue_.pop();

            return std::move(t);
        }

        bool IsEmpty() {
            auto *raw_mutex_ptr = mutex_.get();
            std::lock_guard<std::mutex> lock(*raw_mutex_ptr);

            return queue_.empty();
        }
};

class IWorker
{
    protected:
        IWorker() = default;

    public:
        virtual void AddTask(const Task& task) = 0;
        virtual void Shutdown() = 0;

        virtual ~IWorker() = default;
};

class Worker : public IWorker
{
    private:
        int name_ = 0;
        ThreadSafeQueue queue_;

        std::atomic<bool> is_shutdown_ = false;
        std::thread thread_;

        static void MainWorkLoop_(const int name, std::atomic<bool>& is_shutdown, ThreadSafeQueue& queue) {
            while (!is_shutdown.load()) {
                if (queue.IsEmpty()) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    continue;
                }

                auto task = queue.Pop();
                std::cout << "Worker " << name << " has processed task: " << task.data << std::endl;
            }
        }

    public:
        Worker(const int name) : name_(name) {
            std::cout << "Create worker " << name_ << std::endl;
            thread_ = std::thread(MainWorkLoop_, name_, std::ref(is_shutdown_), std::ref(queue_));
        }

        ~Worker() {
            Shutdown();
            thread_.join();
            std::cout << "Destroy worker " << name_ << std::endl;
        };

        Worker(const Worker& rhs) = delete;
        Worker& operator=(const Worker& rhs) = delete;

        void AddTask(const Task& task) override {
            queue_.Push(task);
        }

        void Shutdown() override {
            if (is_shutdown_.load()) {
                return;
            }

            is_shutdown_.store(true);
            std::cout << "Shutdown worker " << name_ << std::endl;
        }
};

class IProducer
{
    protected:
        IProducer() = default;

    public:
        virtual Task GetTask() = 0;
        virtual bool IsEmpty() = 0;
        virtual void Shutdown() = 0;

        virtual ~IProducer() = default;
};

class Producer : public IProducer
{
    private:
        int name_ = 0;
        ThreadSafeQueue queue_;

        std::atomic<bool> is_shutdown_ = false;
        std::thread thread_;

        static void MainProduceLoop_(const int name, std::atomic<bool>& is_shutdown, ThreadSafeQueue& queue) {
            while (!is_shutdown.load()) {
                queue.Push({.data = "new task"});
                std::cout << "Producer " << name << " has produced task" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

    public:
        Producer(const int name) : name_(name) {
            std::cout << "Create producer " << name_ << std::endl;
            thread_ = std::thread(MainProduceLoop_, name_, std::ref(is_shutdown_), std::ref(queue_));
        }

        ~Producer() {
            Shutdown();
            thread_.join();
            std::cout << "Destroy producer " << name_ << std::endl;
        };

        Producer(const Producer& rhs) = delete;
        Producer& operator=(const Producer& rhs) = delete;

        Task GetTask() override {
            return queue_.Pop();
        }

        bool IsEmpty() override {
            return queue_.IsEmpty();
        }

        void Shutdown() override {
            if (is_shutdown_.load()) {
                return;
            }

            is_shutdown_.store(true);
            std::cout << "Shutdown producer " << name_ << std::endl;
        }
};

using UniqueWorkers = std::vector<std::unique_ptr<IWorker>>;
using UniqueProducers = std::vector<std::unique_ptr<IProducer>>;

class Scheduler {
    private:
        std::atomic<bool> is_shutdown_ = false;
        std::thread thread_;

        UniqueWorkers& workers_;
        UniqueProducers& producers_;

        static void MainSchedLoop_(std::atomic<bool>& is_shutdown, UniqueWorkers& workers, UniqueProducers& producers) {
            std::queue<Task> tasks;

            while (!is_shutdown.load()) {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                for (auto& p : producers) {
                    if (p->IsEmpty()) {
                        continue;;
                    }
                    tasks.push(p->GetTask());
                }

                while (!tasks.empty()) {
                    for (auto& w : workers) {
                        if (tasks.empty()) {
                            break;
                        }

                        auto task = tasks.front();
                        tasks.pop();

                        w->AddTask(task);
                        std::cout << "Scheduler has assing task" << std::endl;
                    }
                }
            }
        }

    public:
        Scheduler(UniqueWorkers& workers, UniqueProducers& producers) : workers_(workers), producers_(producers) {
            std::cout << "Create scheduler" << std::endl;
            thread_ = std::thread(MainSchedLoop_, std::ref(is_shutdown_), std::ref(workers_), std::ref(producers_));
        }

        ~Scheduler() {
            Shutdown();
            thread_.join();
            std::cout << "Destroy scheduler" << std::endl;
        };

        Scheduler(const Scheduler& rhs) = delete;
        Scheduler& operator=(const Scheduler& rhs) = delete;

        Scheduler(Scheduler&& rhs) = delete;
        Scheduler& operator=(Scheduler&& rhs) = delete;

        void Shutdown() {
            if (is_shutdown_.load()) {
                return;
            }

            is_shutdown_.store(true);
            std::cout << "Shutdown scheduler " << std::endl;
        }
};

std::unique_ptr<IWorker> CreateWorker(const int name) {
    return std::make_unique<Worker>(name);
}

std::unique_ptr<IProducer> CreateProducer(const int name) {
    return std::make_unique<Producer>(name);
}

int main(/* args */) {
    const auto n_workers = 10;

    UniqueWorkers workers;
    UniqueProducers producers;

    workers.reserve(n_workers);
    producers.reserve(n_workers);

    std::cout << "Start scheduler programm..." << std::endl;

    for (auto i = 0; i < n_workers; ++i) {
        producers.emplace_back(CreateProducer(i));
        workers.emplace_back(CreateWorker(i));
    }

    Scheduler scheduler(workers, producers);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Finish scheduler programm..." << std::endl;

    return 0;
}
