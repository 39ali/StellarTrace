
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "../vendor/stb_image_write.h"
#include "Core.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Math/Vector3f.h"
#include "Ray.h"
#include "Sphere.h"
#include <limits>
using namespace StellarTrace;

vec3 color(const Ray &r, HitableList *world) {

  HitRecord rec;
  if (world->Hit(r, 0.0, std::numeric_limits<float>::max(), rec)) {
    return 0.5 * (rec.normal + 1.0);
  }

  vec3 dir = r.Direction.normalize();
  // convert from -1 - +1 to 0-1
  float t = 0.5 * (dir.y + 1.0);
  return (1.0 - t) * vec3(1) + (t)*vec3(0.5, 0.7, 1.0);
}
int main() {

  float w = 300, h = 200;
  uint8_t *data1 = new uint8_t[w * h * 3];
  vec3 lowerLeftCorner(-2, -1, -1);
  vec3 horizontal(4, 0, 0);
  vec3 vertical(0, 2, 0);
  vec3 origin(0);
  HitableList *world = new HitableList();
  world->Add(new Sphere(vec3(0, 0, -1), 0.5));
  world->Add(new Sphere(vec3(0, -100.5, -1), 100));
#if 1
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {

      const int pos = y * w * 3 + x * 3;
      const float u = float(x) / w;
      const float v = float(y) / h;
      const Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
      const vec3 col = color(r, world);
      data1[pos + 0] = uint8(255 * col.x);
      data1[pos + 1] = uint8(255 * col.y);
      data1[pos + 2] = uint8(255 * col.z);
    }
  }
#endif
  stbi_flip_vertically_on_write(1);
  stbi_write_png("f1.png", w, h, 3, data1, w * 3);
}
