#pragma once

namespace StellarTrace {

class Vector2f {
 public:
  float x, y;
  Vector2f() : x(0), y(0){};
  Vector2f(float _x, float _y) : x(_x), y(_y){};
};
using vec2f = Vector2f;
}  // namespace StellarTrace
