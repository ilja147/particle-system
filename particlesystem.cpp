#include "particlesystem.h"
#include <random>
#include <thread>
#include <algorithm>
ParticleSystem::ParticleSystem()
{
    threadcount = std::thread::hardware_concurrency();
    if (threadcount == 0)
    {
        threadcount = 5;
    }
    particles.resize(threadcount);
}
void ParticleSystem::addparticles(int mincount, int maxcount, int lifetime, int baseColorIndex = 0)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(mincount,maxcount);
    int count = dist(gen);
    int chunk_size = std::max(1, count/threadcount);
    size_t current_vector = 0;
    int j = 0;
    int minx = 0, maxx= 800;
    std::uniform_int_distribution<int>particlex(minx,maxx);
    std::uniform_int_distribution<int>totallifetime(100,lifetime);
    std::uniform_int_distribution<int>color(0,9);
    size_t nextId=0;
    //particles.resize(threadcount);
    for (int i = 0; i < count; i++)
    {
        Particle newParticle;
        newParticle.x = particlex(gen);
        newParticle.y = 640;
        newParticle.startx = newParticle.x;
        newParticle.starty = newParticle.y;
        newParticle.lifetime = totallifetime(gen);
        newParticle.maxlifetime = lifetime;
        newParticle.id = nextId++;
        newParticle.colorindex = baseColorIndex + color(gen);
        if(particles[j].size() == chunk_size && j < threadcount-1)
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
    thread_local std::uniform_real_distribution<float> dist(-2.5f,2.5f);
    thread_local std::uniform_int_distribution<int> lifetime(100,bucket[0].maxlifetime);
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
            //particle.isActive = false;
            particle.lifetime = lifetime(gen);
            particle.speedx = 0;
            particle.speedy = 0;
            particle.x = particle.startx;
            particle.y = particle.starty;
        }
        if(particle.isActive)
        {
            particle.x+=dist(gen);
            particle.y+=dist(gen);
        }
    }
}
// void ParticleSystem::removeDeadParticles()
// {
//     for(auto &bucket : particles)
//     {
//         bucket.erase(std::remove_if(bucket.begin(), bucket.end(),[](const Particle &p){return !p.isActive || p.lifetime <= 0;}),bucket.end());
//     }
// }
void ParticleSystem::updateparticles(float deltaTime)
{
    std::vector<std::thread> threads;
    for(int i = 0; i < particles.size();i++)
    {
        threads.emplace_back(&ParticleSystem::updateParticleBucket, this, std::ref(particles[i]),deltaTime);
    }
    for(std::thread &i : threads)
    {
        i.join();
    }
    //removeDeadParticles();
}
const std::vector<std::vector<Particle>> &ParticleSystem::getParticles() const
{
    return particles;
}
void ParticleSystem::addforce(std::unique_ptr<Force> force)
{
    forces.push_back(std::move(force));
}
