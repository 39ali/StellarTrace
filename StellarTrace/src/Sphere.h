#pragma once
#include "Hitable.h"
namespace StellarTrace {
class Sphere : public Hitable {
public:
  Sphere() {}
  Sphere(vec3 center, float r, Material *_material)
      : Center(center), Radius(r), material(_material){};
  virtual bool Hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const;
  vec3 Center;
  float Radius;
  Material *material;
};

bool Sphere::Hit(const Ray &r, float tmin, float tmax, HitRecord &rec) const {
  vec3 oc = r.Origin - Center;
  const float a = r.Direction.dot(r.Direction);
  const float b = 2.0 * (r.Direction.dot(oc));
  const float c = oc.dot(oc) - Radius * Radius;
  float d = b * b - 4 * a * c;
  if (d > 0) {
    rec.material = material;
    float temp = (-b - sqrtf(d)) / (2.0 * a);
    if (temp < tmax && temp > tmin) {
      rec.t = temp;
      rec.position = r.PointAt(temp);
      rec.normal = (rec.position - Center).normalize();
      return true;
    }
    temp = (-b + sqrtf(d)) / (2.0 * a);
    if (temp < tmax && temp > tmin) {
      rec.t = temp;
      rec.position = r.PointAt(temp);
      rec.normal = (rec.position - Center).normalize();
      return true;
    }
  }
  return false;
}

} // namespace StellarTrace
