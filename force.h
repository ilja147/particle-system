#pragma once
class Force
{
protected:
    Force(const Force&) = delete;
    Force &operator=(const Force&) = delete;
    Force() = default;
public:
    virtual void applyForce(float x, float y, float &speedx, float &speedy) = 0;
    virtual ~Force() = default;
};
