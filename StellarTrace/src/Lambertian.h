#pragma once
#include "Material.h"

namespace StellarTrace {

class Lambertian : public Material {
public:
  Lambertian(const vec3 &a) : Albedo(a) {}
  virtual bool Scatter(const Ray &r, const HitRecord &rec, vec3 &attenuation,
                       Ray &scattered) const {
    vec3 target = rec.position + rec.normal + random_sphere();
    scattered = Ray(rec.position, target - rec.position);
    attenuation = Albedo;
    return true;
  }
  vec3 Albedo;
};

} // namespace StellarTrace
