#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    Semaphore();

private:
    std::mutex mutex;
    std::condition_variable conditionVariable;
};

#endif // SEMAPHORE_H
