#include <iostream>
#include <chrono>
#include "particlesystem.h"
using namespace std;

int main()
{
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    TimePoint previousTime = Clock::now();
    cout << "Hello World!" << endl;
    return 0;
}
