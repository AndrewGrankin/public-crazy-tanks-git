// this is a test Thread Pool implementaion

#ifndef TEST_THREAD_POOL_H
#define TEST_THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

using namespace std;

class TestThreadPool
{
    public:
        TestThreadPool(size_t);
        ~TestThreadPool();

        template<class T, class... Args>
        auto enqueue(T&& t, Args&&... args) -> future<typename result_of<T(Args...)>::type>;

    private:
        // need to keep track of threads so we can join them
        vector<thread> workers;

        // the task queue
        queue<function<void()>> tasks;

        // synchronization
        mutex queue_mutex;
        condition_variable condition;
        bool stop;
};

// the constructor just launches some amount of workers
inline TestThreadPool::TestThreadPool(size_t threads) : stop (false)
{
    for (size_t i = 0; i < threads; ++i)
    {
        workers.emplace_back(
            [this] 
            {
                for(;;)
                {
                    function<void()> task;
                    {
                        unique_lock<mutex> ul (this->queue_mutex);
                        this->condition.wait(ul, [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                        {
                            return;
                        }
                        task = move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }
}

template<class T, class... Args>
auto TestThreadPool::enqueue(T&& t, Args&&... args) -> future<typename result_of<T(Args...)>::type>
{
    using return_type = typename result_of<T(Args...)>::type;

    auto task = make_shared<packaged_task<return_type()>>(
            bind(forward<T>(t), forward<Args>(args)...)
        );

    future<return_type> res = task->get_future();
    {
        unique_lock<mutex> ul(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
        {
            throw runtime_error("enqueue on stopped TestThreadPool");
        }

        tasks.emplace([task](){(*task)();});
    }
    condition.notify_one();
    return res;
}

// the destructor joins all threads
inline TestThreadPool::~TestThreadPool()
{
    {
        unique_lock<mutex> ul(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (thread& worker: workers)
    {
        worker.join();
    }
}

#endif