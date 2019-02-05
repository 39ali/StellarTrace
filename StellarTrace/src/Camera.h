#pragma once
#include "Ray.h"

namespace StellarTrace {

class Camera {
public:
  Camera() {
    LowerLeftCorner = vec3(-2, -1, -1);
    Horizontal = vec3(4, 0, 0);
    Vertical = vec3(0, 2, 0);
    Origin = vec3(0);
  }
  inline Ray GetRay(float u, float v) const {
    return Ray(Origin,
               LowerLeftCorner + u * Horizontal + v * Vertical );
  }
  vec3 Origin;
  vec3 LowerLeftCorner;
  vec3 Horizontal;
  vec3 Vertical;
};

} // namespace StellarTrace
