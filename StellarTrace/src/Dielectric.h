#pragma once
#include "Material.h"
namespace StellarTrace {
	///@TODO: dialect objects are flipped ,fix that 
class Dielectric : public Material {
public:
  Dielectric(float refractionIndex) : RefractionIndex(refractionIndex) {}
  virtual bool Scatter(const Ray &r, const HitRecord &rec, vec3 &attenuation,
                       Ray &scattered) const {
    vec3 outward_normal;
    vec3 reflected = Reflect(r.Direction, rec.normal);
	
    float ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;

    if (r.Direction.dot(rec.normal) > 0) {
      outward_normal = -rec.normal;
      ni_over_nt = RefractionIndex;
      /*   cosine = RefractionIndex * (r.Direction.dot(rec.normal)) /
                  r.Direction.length();*/
      cosine = RefractionIndex * (r.Direction.dot(rec.normal)) /
               r.Direction.length();
      /*cosine =
          sqrt(1 - RefractionIndex * RefractionIndex * (1 - cosine * cosine));*/
    } else {
      outward_normal = rec.normal;
      ni_over_nt = 1.0f / RefractionIndex;
      cosine = -(r.Direction.dot(rec.normal)) / r.Direction.length();
    }

    if (Refract(r.Direction, outward_normal, ni_over_nt, refracted))
      reflect_prob = Schlick(cosine, RefractionIndex);
    else {
      reflect_prob = 1.0f;
    }

    if (((float)std::rand() / RAND_MAX) < reflect_prob)
      scattered = Ray(rec.position, reflected);
    else {
      scattered = Ray(rec.position, refracted);
    }
    return true;
  }

  bool Refract(const vec3 &v, const vec3 &n, float ni_over_nt,
               vec3 &refracted) const noexcept {
    vec3 vn = v.normalize();
    float dt = vn.dot(n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0.0) {
      refracted = ni_over_nt * (vn - dt * n) - std::sqrtf(discriminant) * n;
      // refracted = -refracted;
      return true;
    }
    return false;
  }
  float Schlick(float cosine, float refIdx) const {
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 *= r0;
    return r0 + (1 - r0) * std::powf(1 - cosine, 5);
  }
  float RefractionIndex;
};

} // namespace StellarTrace
