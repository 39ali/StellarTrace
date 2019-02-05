#pragma once
#include "Math/Vector3f.h"
#include "Ray.h"
namespace StellarTrace {

struct HitRecord {
  float t; // parameter t 
  vec3 position; // the position of the hit 
  vec3 normal;
};

class Hitable {
public:
  virtual bool Hit(const Ray &r, float tmin, float tmax,
                   HitRecord &rec) const = 0;
};

} // namespace StellarTrace
