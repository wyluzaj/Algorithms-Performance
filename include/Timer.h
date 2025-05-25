#ifndef AIZO_SORT_TIMER_H
#define AIZO_SORT_TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    void reset();
    int start();
    int stop();
    int result();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
};

#endif // AIZO_SORT_TIMER_H
