#pragma once
#include "Hitable.h"
#include "Ray.h"
namespace StellarTrace {

vec3 random_sphere() {
  vec3 p;

  do {
    p = 2.0 * vec3(((float)std::rand() / RAND_MAX),
                   ((float)std::rand() / RAND_MAX),
                   ((float)std::rand() / RAND_MAX)) -
        vec3(1);
  } while (p.length() >= 1.0);
  return p;
}
vec3 Reflect(const vec3& v, const vec3& n) {
	return v - 2 * (n.dot(v))*n;
}

class Material {

public:
  virtual bool Scatter(const Ray &r, const HitRecord &rec, vec3 &attenuation,
                       Ray &scattered) const = 0;
};
} // namespace StellarTrace
