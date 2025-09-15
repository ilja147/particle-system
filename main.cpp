#include <iostream>
#include <chrono>
#include "particlesystem.h"
#include "firegravity.h"
#include "gravityforce.h"
#include "windforce.h"
using namespace std;

int main()
{
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    TimePoint previousTime = Clock::now();
    auto firegravity = std::make_unique<FireGravity>(1.0f);
    ParticleSystem ps;
    ps.addforce(std::move(firegravity));
    cout << "Hello World!" << endl;
    return 0;
}
