// This is to test threads

#include <iostream>
#include <thread>
#include <chrono>

#include <SimpleThreadPool.h>

using namespace std::chrono;

mutex flagMutex;

void Hello()
{
    std::cout << "Hello, Concurrent World!\n";
}

void WaitForShoot(int time, bool& flag)
{
    lock_guard<mutex> lg(flagMutex);
    flag = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    flag = true;
}

int main()
{
    std::thread hello_thread(Hello);
    hello_thread.join();
    int currentTime = (int)time(0);
    int64_t currentTimeLong = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    cout << endl << "hardware_concurrency() value =  " << thread::hardware_concurrency() << endl;
    cout << "(int)time(0) = " << currentTime << endl;
    cout << "system_clock::now() = " << currentTimeLong;

    // SimpleThreadPool threadPool;
    // function<void(char)> work_function;
    // threadPool.Submit(Work('+'));

    std::cin.get();
    return 0;
}