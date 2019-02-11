#pragma once
#include "Hitable.h"
#include "Ray.h"
namespace StellarTrace {

class Material {

public:
  virtual bool Scatter(const Ray &r, const HitRecord &rec, vec3 &attenuation,
                       Ray &scattered) const = 0;
};
} // namespace StellarTrace
