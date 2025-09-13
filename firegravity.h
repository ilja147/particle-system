#pragma once
#include "force.h"
class FireGravity : public Force
{
    float strength = 9.8f;
public:
    FireGravity();
    FireGravity(float a);
    void applyForce(float x, float y, float &speedx, float &speedy) override;
    ~FireGravity() = default;
};
