#pragma once
#include "Ray.h"
#define PIE 3.14f
namespace StellarTrace {

class Camera {
public:
  // fov is in degrees also it's vertical
  Camera(const vec3 &eye, const vec3 &lookAt, const vec3 &up, float fov,
         float aspectRatio) {
    vec3 u, v, w;
    float th = fov * PIE / 180.f;
    float halfH = tanf(th / 2);
    float halfW = aspectRatio * halfH;
	Origin = eye;
	w = (eye - lookAt).normalize();
	u = up.cross(w).normalize();
	v = w.cross(u);
    //LowerLeftCorner = vec3(-halfW, -halfH, -1);
	LowerLeftCorner = Origin - halfW * u - halfH * v - w;
	Horizontal = 2 * halfW*u;
    Vertical = 2 * halfH*v;
   
  }
  inline Ray GetRay(float u, float v) const {
    return Ray(Origin, LowerLeftCorner + u * Horizontal + v * Vertical -Origin);
  }
  vec3 Origin;
  vec3 LowerLeftCorner;
  vec3 Horizontal;
  vec3 Vertical;
};

} // namespace StellarTrace
