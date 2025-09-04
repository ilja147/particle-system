#include "gravityforce.h"

GravityForce::GravityForce(){}
GravityForce::GravityForce(float a)
{
    strength = strength * a;
}
void GravityForce::applyForce(float x, float y, float &speedx, float &speedy)
{
    speedy += strength;
}
