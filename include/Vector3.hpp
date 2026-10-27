#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>
#include <iostream>

struct Vector3 {
    double x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vector3 operator-(const Vector3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vector3 operator*(double t) const { return {x * t, y * t, z * t}; }
    Vector3 operator/(double t) const { return {x / t, y / t, z / t}; }

    double lengthSquared() const { return x * x + y * y + z * z; }
    double length() const { return std::sqrt(lengthSquared()); }

    Vector3 normalize() const {
        return *this / length();
    }

    static double dot(const Vector3& u, const Vector3& v) {
        return u.x * v.x + u.y * v.y + u.z * v.z;
    }
};

inline Vector3 operator*(double t, const Vector3& v) {
    return v * t;
}

#endif // VECTOR3_HPP
