#pragma once
#include <cstddef>
struct Particle
{
    float x,y;
    int lifetime;
    bool isActive;
    float speedx;
    float speedy;
    int colorindex;
    std::size_t id;
    Particle():colorindex(1),lifetime(1),x(0),y(0),speedx(0),speedy(0),isActive(true){}
    Particle(int a):colorindex(a),lifetime(1),x(0),y(0),speedx(0),speedy(0),isActive(true){}
    Particle(int a, int b):colorindex(a),lifetime(b),x(0),y(0),speedx(0),speedy(0),isActive(true){}
    Particle(float x, float y, int a): x(x), y(y), colorindex(a),lifetime(1),speedx(0),speedy(0),isActive(true){}
    Particle(float x, float y, int a, int b):x(x),y(y),colorindex(a),lifetime(b),speedx(0),speedy(0),isActive(true){}
};
