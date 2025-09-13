#pragma once
#include "force.h"
#include "particle.h"
#include <vector>
#include <memory>
class ParticleSystem
{

    int particlesPerSecond;
    std::vector<std::vector<Particle>> particles;
    void updateParticleBucket(std::vector<Particle> &bucket, float deltaTime);
    void removeDeadParticles();
    std::vector<std::unique_ptr<Force>>forces;
public:
    ParticleSystem();
    void addparticles(int mincount,int maxcount, int lifetime);
    void updateparticles(float deltaTime);
};
