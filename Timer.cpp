#include "include/Timer.h"

Timer::Timer() = default;

void Timer::reset() {
    startTime = std::chrono::high_resolution_clock::now();
    endTime = startTime;
}

int Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    return 0;
}

int Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    return 0;
}

int Timer::result() {
    std::chrono::duration elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return static_cast<int>(elapsed.count());
}
