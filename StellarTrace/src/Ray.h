#pragma once
#include "Math/Vector3f.h"

namespace StellarTrace {

class Ray {

public:
  Ray(const vec3 &origin, const vec3 &direction): Origin(origin), Direction(direction) {}
  vec3 PointAt(float t)const  { return Origin + t * Direction; }
  vec3 Origin, Direction;
};

} // namespace StellarTrace
