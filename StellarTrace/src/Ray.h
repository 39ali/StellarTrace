#pragma once
#include "Math/Vector3f.h"

namespace StellarTrace {

class Ray {

public:
	Ray():Origin(vec3(0)),Direction(vec3(0)) {}
  Ray(const vec3 &origin, const vec3 &direction): Origin(origin), Direction(direction) {}
  vec3 PointAt(float t)const  { return Origin + t * Direction; }
  vec3 Origin, Direction;
};

} // namespace StellarTrace
