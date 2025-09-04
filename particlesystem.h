#pragma once
#include "force.h"
#include "particle.h"
#include <vector>
#include <unordered_map>
class ParticleSystem
{
    void addparticles(int mincount,int maxcount);
    int countparticles;
    void updateparticles();
    int particlesPerSecond;
    std::unordered_map<ParticleId,Particle> particles;
    void useforce(std::vector<force>forces);
public:
    ParticleSystem();
};
