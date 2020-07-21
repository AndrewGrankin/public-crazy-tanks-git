// SimpleThreadPool/SimpleThreadPool.h

#ifndef SIMPLE_THREAD_POOL
#define SIMPLE_THREAD_POOL

#include <atomic>
#include <vector>
#include <thread>

#include <ThreadSafeQueue.h>
#include <JoinThreads.h>


using namespace std;

class SimpleThreadPool
{
    private:
        atomic<bool> done;
        ThreadSafeQueue< function<void(char)> > work_queue;
        vector<thread> threads;
        JoinThreads joiner;

    private:
        void WorkerThread();

    public:
        SimpleThreadPool();
        ~SimpleThreadPool();

        template <typename FunctionType>
        void Submit(FunctionType f);
};

SimpleThreadPool::SimpleThreadPool() : done(false), joiner(threads)
{
    unsigned const thread_count = thread::hardware_concurrency();

    try
    {
        for (unsigned i = 0; i < thread_count; ++i)
        {
            threads.push_back(thread(&SimpleThreadPool::WorkerThread, this));
        }
    }
    catch (...)
    {
        done = true;
        throw;
    }
}

SimpleThreadPool::~SimpleThreadPool()
{
    done = true;
}

void SimpleThreadPool::WorkerThread()
{
    while (!done)
    {
        function<void(char)> task;
        if (work_queue.TryPop(task))
        {
            task('-');
        }
        else
        {
            this_thread::yield();
        }
    }
}

template <typename FunctionType>
void SimpleThreadPool::Submit(FunctionType f)
{
    work_queue.Push(function<void(char)>(f));
}

#endif