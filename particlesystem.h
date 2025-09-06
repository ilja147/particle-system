#pragma once
#include "force.h"
#include "particle.h"
#include <vector>
#include <memory>
class ParticleSystem
{
    void addparticles(int mincount,int maxcount, int lifetime);
    void updateparticles();
    int particlesPerSecond;
    std::vector<std::vector<Particle>> particles;
    void useforce(std::unique_ptr<std::vector<Force>>forces);
public:
    ParticleSystem();
};
