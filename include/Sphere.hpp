#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Ray.hpp"

struct HitRecord {
    Vector3 p;
    Vector3 normal;
    double t;
    bool hit;
};

class Sphere {
public:
    Vector3 center;
    double radius;

    Sphere(const Vector3& cen, double r) : center(cen), radius(r) {}

    HitRecord hit(const Ray& r, double tMin, double tMax) const {
        HitRecord rec{Vector3(), Vector3(), 0.0, false};
        Vector3 oc = r.orig - center;
        auto a = r.dir.lengthSquared();
        auto halfB = Vector3::dot(oc, r.dir);
        auto c = oc.lengthSquared() - radius * radius;
        auto discriminant = halfB * halfB - a * c;

        if (discriminant < 0) return rec;
        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        auto root = (-halfB - sqrtd) / a;
        if (root < tMin || rootMax < root) {
            root = (-halfB + sqrtd) / a;
            if (root < tMin || tMax < root)
                return rec;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vector3 outwardNormal = (rec.p - center) / radius;
        rec.normal = outwardNormal;
        rec.hit = true;
        return rec;
    }
};

#endif // SPHERE_HPP
