#include "particlesystem.h"
#include <random>
ParticleSystem::ParticleSystem() {}
void ParticleSystem::addparticles(int mincount, int maxcount, int lifetime)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(mincount,maxcount);
    int count = dist(gen);
    int chunk_size = count/1000;
    size_t current_vector = 0;
    int j = 0;
    int minx = 0, maxx= 10;
    std::uniform_int_distribution<int>particlex(minx,maxx);
    std::uniform_int_distribution<int>totallifetime(100,lifetime);
    std::uniform_int_distribution<int>color(0,9);
    size_t nextId=0;
    for (int i = 0; i < count; i++)
    {
        Particle newParticle;
        newParticle.x = particlex(gen);
        newParticle.y = 0;
        newParticle.lifetime = totallifetime(gen);
        newParticle.id = nextId++;
        newParticle.colorindex = color(gen);
        if(particles[j].size() == chunk_size)
        {
            particles[j].reserve(1000);
            j++;
        }
        particles[j].push_back(std::move(newParticle));
    }
}
void updateparticles()
{
    std::vector<std::thread>
}
