#include "particlesystem.h"
#include <random>
#include <thread>
#include <algorithm>
ParticleSystem::ParticleSystem()
{
    int threadcount = std::thread::hardware_concurrency();
    if (threadcount == 0)
    {
        threadcount = 4;
    }
    particles.resize(threadcount);
}
void ParticleSystem::addparticles(int mincount, int maxcount, int lifetime)
{
    int threadcount = 0;
    threadcount = std::thread::hardware_concurrency();
    if(threadcount == 0)
    {
        threadcount = 4;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(mincount,maxcount);
    int count = dist(gen);
    int chunk_size = std::max(1, count/threadcount);
    size_t current_vector = 0;
    int j = 0;
    int minx = 0, maxx= 10;
    std::uniform_int_distribution<int>particlex(minx,maxx);
    std::uniform_int_distribution<int>totallifetime(100,lifetime);
    std::uniform_int_distribution<int>color(0,9);
    size_t nextId=0;
    particles.resize(threadcount);
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
            j++;
            particles[j].reserve(chunk_size);
        }
        particles[j].push_back(std::move(newParticle));
    }
}
void ParticleSystem::updateParticleBucket(std::vector<Particle> &bucket, float deltaTime)
{
    thread_local std::mt19937 gen(std::random_device{}());
    thread_local std::uniform_real_distribution<float> dist(-0.5f,0.5f);
    for(Particle &particle : bucket)
    {
        for(auto &force : forces)
        {
            force->applyForce(particle.x, particle.y, particle.speedx,particle.speedy);
        }

        particle.x = particle.x + particle.speedx * deltaTime;
        particle.y = particle.y + particle.speedy * deltaTime;
        particle.lifetime--;
        if(particle.lifetime <= 0)
        {
            particle.isActive = false;
        }
        if(particle.isActive)
        {
            particle.x+=dist(gen);
            particle.y+=dist(gen);
        }
    }
}
void ParticleSystem::removeDeadParticles()
{
    for(auto &bucket : particles)
    {
        bucket.erase(std::remove_if(bucket.begin(), bucket.end(),[](const Particle &p){return !p.isActive || p.lifetime <= 0;}),bucket.end());
    }
}
void ParticleSystem::updateparticles(float deltaTime)
{
    std::vector<std::thread> threads;
    for(int i = 0; i < particles.size();i++)
    {
        try
        {
            threads.emplace_back(&ParticleSystem::updateParticleBucket, this, std::ref(particles[i]),deltaTime);
        }
        catch(const std::exception &e)
        {
            //на будущее
        }
        }
    for(std::thread &i : threads)
    {
        i.join();
    }
    removeDeadParticles();
}
const std::vector<std::vector<Particle>> &ParticleSystem::getParticles() const
{
    return particles;
}
