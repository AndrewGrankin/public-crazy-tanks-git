// SimpleThreadPool/ThreadSafeQueue.h

#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include <queue>
#include <memory>       // for shared_ptr
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class ThreadSafeQueue
{
    private:
        mutable mutex mut;      // the mutex must be mutable
        queue<T> data_queue;
        condition_variable data_cond;

    public:
        ThreadSafeQueue() {}
        ThreadSafeQueue(ThreadSafeQueue const& other)
        {
            lock_guard<mutex> lg(other.mut);
            data_queue = other.data_queue;
        }

        void Push(T new_value)
        {
            lock_guard<mutex> lg(mut);
            data_queue.push(new_value);
            data_cond.notify_one();
        }

        void WaitAndPop(T& value)
        {
            unique_lock<mutex> ul(mut);
            data_cond.wait(ul, [this]{return !data_queue.empty();});
            value = data_queue.front();
            data_queue.pop();
        }

        shared_ptr<T> WaitAndPop()
        {
            unique_lock<mutex> ul(mut);
            data_cond.wait(ul, [this]{return !data_queue.empty();});
            shared_ptr<T> result(make_shared<T>(data_queue.front()));
            data_queue.pop();
            return result;
        }

        bool TryPop(T& value)
        {
            lock_guard<mutex> lg(mut);
            if (data_queue.empty())
            {
                return false;
            }
            value = data_queue.front();
            data_queue.pop();
            return true;
        }

        shared_ptr<T> TryPop()
        {
            lock_guard<mutex> lg(mut);
            if (data_queue.empty())
            {
                return shared_ptr<T>();
            }
            shared_ptr<T> result(make_shared<T>(data_queue.front()));
            data_queue.pop();
            return result;
        }

        bool Empty() const
        {
            lock_quard<mutex> lg(mut);
            return data_queue.empty();
        }
};

#endif