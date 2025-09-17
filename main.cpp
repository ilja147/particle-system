#include <iostream>
#include <chrono>
#include <memory>
#include "particlesystem.h"
#include "render.h"
#include "firegravity.h"
#include "gravityforce.h"
#include "windforce.h"
using namespace std;

int main()
{
    Renderer renderer(800,600);
    if(!renderer.Init())
    {
        SDL_Quit();
        return 1;
    }
    ParticleSystem ps;
    //ps.addforce(std::make_unique<FireGravity>(0.8f));
    ps.addforce(std::make_unique<WindForce>(0.0f,0.0f));
    ps.addparticles(50000,100000,300,0);// 1: mincounnt, 2:maxcount, 3:lifetime, 4:color index
    auto lastTime = std::chrono::high_resolution_clock::now();
    while(renderer.isRunning())
    {
        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTime).count();
        lastTime = now;
        ps.updateparticles(deltaTime);
        renderer.render(ps);
    }
    SDL_Quit();
    return 0;
}
