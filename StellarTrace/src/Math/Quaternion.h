#pragma once

#include "Vector3f.h"

namespace StellarTrace {	
	class Quaternion {
public :
	Quaternion() { x = y = z = w = 0.0f; }
  Quaternion(float _x, float _y, float _z, float w);
  Quaternion normalize()const ;
  Quaternion conjugate()const ;
  vec3 quatToDegrees()const;
  static vec3 rotate(float angle, const vec3& axe, const vec3& v);
  float x, y, z, w;
};

	Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

	Quaternion operator*(const Quaternion& q, const vec3& v);
}  // namespace StellarTrace
