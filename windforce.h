#include "force.h"
#pragma once
class WindForce : public Force
{
    float directionx, directiony;

public:
    WindForce();
    WindForce(float a, float b);
    void applyForce(float x, float y, float &speedx, float &speedy) override;
    ~WindForce() = default;
};
