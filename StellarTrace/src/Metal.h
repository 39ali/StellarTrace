#pragma once
#include "Material.h"

namespace StellarTrace {

class Metal : public Material {
public:
  Metal(const vec3 &albedo, float fuzz) : Albedo(albedo) {
    if (Fuzz < 1)
      Fuzz = fuzz;
    else
      Fuzz = 1;
  }
  virtual bool Scatter(const Ray &r, const HitRecord &rec, vec3 &attenuation,
                       Ray &scattered) const override {
    vec3 reflect = Reflect(r.Direction.normalize(), rec.normal);
    scattered = Ray(rec.position, reflect+Fuzz*random_sphere());
    attenuation = Albedo;
    return scattered.Direction.dot(rec.normal) > 0;
  }
  vec3 Albedo;
  float Fuzz;
};

} // namespace StellarTrace
