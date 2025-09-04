#include "force.h"

class GravityForce : public Force
{
    static inline float GRAVITY_CONST = 9.8f;
    ~GravityForce() = default;
public:
    GravityForce(){}
    GravityForce(float a)
    {
        GRAVITY_CONST = GRAVITY_CONST * a;
    }
    void applyForce(float x, float y, float &speedx, float &speedy) override
    {
        speedy += GRAVITY_CONST;
    }
};
class WindForce : public Force
{
    float directionx, directiony;
    ~WindForce() = default;
public:
    WindForce(){}
    WindForce(float a, float b):directionx(a),directiony(b){}
    void applyForce(float x, float y, float &speedx, float &speedy) override
    {
        speedx += directionx;
        speedy += directiony;
    }
};
