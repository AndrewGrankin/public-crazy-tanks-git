// SimpleThreadPool/JoinThreads.h

#ifndef JOIN_THREADS
#define JOIN_THREADS

#include <vector>
#include <thread>

using namespace std;

class JoinThreads
{
    private:
        vector<thread>& threads;

    public:
        explicit JoinThreads(vector<thread>& threads_) : threads(threads_)
        {}
        ~JoinThreads()
        {
            for (unsigned long i = 0; i < threads.size(); ++i)
            {
                if (threads[i].joinable())
                {
                    threads[i].join();
                }
            }
        }
};

#endif