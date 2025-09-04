#include "force.h"
#pragma once
class GravityForce : public Force
{
    float strength = 9.8f;
public:
    GravityForce();
    GravityForce(float a);
    void applyForce(float x, float y, float &speedx, float &speedy) override;
    ~GravityForce() = default;
};
