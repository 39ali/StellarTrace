#pragma once
#include <cmath>

namespace StellarTrace {

class Vector3f {
public:
  Vector3f();
  Vector3f(float val);
  Vector3f(float _x, float _y, float _z);
  Vector3f(const Vector3f &vecIn);
  inline float dot(const Vector3f &vecIn) const;
  inline Vector3f cross(const Vector3f &vecIn) const;
  inline Vector3f normalize() const;
  inline float length() const;

  Vector3f operator+(const Vector3f &vec3) const;
  Vector3f &operator+=(const Vector3f &vec3);

  Vector3f operator-(const Vector3f &vec3) const;
  Vector3f &operator-=(const Vector3f &vec3);

  Vector3f operator*(const Vector3f &vec3) const;
  Vector3f operator*(const float value) const;
  Vector3f &operator*=(const Vector3f &vec3);
  Vector3f &operator*=(const float value);

  Vector3f &operator/=(float);
  Vector3f operator/(float) const;
  inline const float *operator&(void)const { return &v[0]; }

  inline const float operator[](unsigned int index) const { return v[index]; }
  



  union {
    struct {
      float x, y, z;
    };
    float v[3];
  };
};

inline float Vector3f::dot(const Vector3f &vecIn) const {
  return x * vecIn.x + y * vecIn.y + z * vecIn.z;
}
inline Vector3f Vector3f::cross(const Vector3f &v) const {
  return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

inline Vector3f Vector3f::normalize() const {
  const float l = length();
  if (l > 0)
    return Vector3f(*this) / l;

  return Vector3f(*this);
}


inline float Vector3f::length() const { return sqrt(x * x + y * y + z * z); }
inline Vector3f operator*(float t, const Vector3f &v) { return v * t; }
inline Vector3f operator-(const Vector3f& v) { return Vector3f(-v.x, -v.y, -v.z); }

using vec3 = Vector3f;

inline vec3 random_sphere() {
	vec3 p;

	do {
		p = 2.0 * vec3(((float)std::rand() / RAND_MAX),
			((float)std::rand() / RAND_MAX),
			((float)std::rand() / RAND_MAX)) -
			vec3(1);
	} while (p.length() >= 1.0);
	return p;
}

inline vec3 Reflect(const vec3& v, const vec3& n) {
	return v - 2 * (n.dot(v))*n;
}
} // namespace StellarTrace
