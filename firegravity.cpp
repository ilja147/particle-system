#include "firegravity.h"
#include<random>
FireGravity::FireGravity(){}
FireGravity::FireGravity(float a)
{
    strength = strength * a;
}
void FireGravity::applyForce(float x, float y, float &speedx, float &speedy)
{
    thread_local std::random_device rd;
    thread_local std::mt19937 gen(rd());
    thread_local std::uniform_int_distribution<int> dist(0,100);
    int chance = dist(gen);
    if(chance > 50)
    {
    speedy += strength;
    }
}
