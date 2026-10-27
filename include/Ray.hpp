#ifndef RAY_HPP
#define RAY_HPP

#include "Vector3.hpp"

struct Ray {
    Vector3 orig;
    Vector3 dir;

    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction) : orig(origin), dir(direction) {}

    Vector3 at(double t) const {
        return orig + dir * t;
    }
};

#endif // RAY_HPP
