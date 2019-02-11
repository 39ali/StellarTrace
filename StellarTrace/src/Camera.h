#pragma once
#include "Ray.h"
#define PIE 3.14f
#include <random>
namespace StellarTrace {

vec3 random_in_unit_disk() {
  vec3 p;
  do {
	  p = 2.0 * vec3(float(std::rand()) / RAND_MAX, float( std::rand()) / RAND_MAX, 0) -
        vec3(1, 1, 0);
  } while (p.dot(p) >= 1.0);
  return p;
}

class Camera {
 public:
  // fov is in degrees also it's vertical
  Camera(const vec3 &eye, const vec3 &lookAt, const vec3 &up, float fov,
         float aspectRatio, float aperture, float focus_dist) {
    lens_r = aperture / 2;
    float th = fov * PIE / 180.f;
    float halfH = tanf(th / 2);
    float halfW = aspectRatio * halfH;
    Origin = eye;
    w = (eye - lookAt).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u);
    // LowerLeftCorner = vec3(-halfW, -halfH, -1);
    LowerLeftCorner = Origin - halfW * u*focus_dist - halfH * v*focus_dist - w*focus_dist;
    Horizontal = 2 * halfW * u*focus_dist;
    Vertical = 2 * halfH * v*focus_dist;
  }
  inline Ray GetRay(float s, float t) const {
	  vec3 rd = lens_r * random_in_unit_disk();
	  vec3 offset = u * rd.x + v * rd.y;
    return Ray(Origin + offset,
               LowerLeftCorner + s * Horizontal + t * Vertical - Origin - offset);
  }
  vec3 Origin;
  vec3 LowerLeftCorner;
  vec3 Horizontal;
  vec3 Vertical;
  vec3 u, v, w;
  float lens_r;
};

}  // namespace StellarTrace
