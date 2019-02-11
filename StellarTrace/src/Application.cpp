
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include <cstdlib>
#include <limits>
#include <random>
#include "../vendor/stb_image_write.h"
#include "Camera.h"
#include "Core.h"
#include "Dielectric.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Lambertian.h"
#include "Math/Vector3f.h"
#include "Metal.h"
#include "Ray.h"
#include "Sphere.h"
//#include <intrin.h>

// simd
// https://stackoverflow.com/questions/11228855/header-files-for-x86-simd-intrinsics
using namespace StellarTrace;

vec3 random_sphere() {
  vec3 p;

  do {
    p = 2.0 * vec3(((float)std::rand() / RAND_MAX),
                   ((float)std::rand() / RAND_MAX),
                   ((float)std::rand() / RAND_MAX)) -
        vec3(1);
  } while (p.length() >= 1.0);
  return p;
}
vec3 color(const Ray &r, HitableList *world, int depth) {
  HitRecord rec;

  if (world->Hit(r, 0.01, std::numeric_limits<float>::max(), rec)) {
    Ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    } else
      return vec3(0);
  }
  vec3 dir = r.Direction.normalize();
  // convert from -1 - +1 to 0-1
  float t = 0.5 * (dir.y + 1.0);
  return (1.0 - t) * vec3(1) + (t)*vec3(0.5, 0.7, 1.0);
}

#define DRAND (float)std::rand() / RAND_MAX
HitableList objects;
void RandomScene() {
  const int c = 5;
  objects.Add(new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5))));
  int i = 1;
  for (int a = -c; a < c; a++) {
    for (int b = -c; b < c; b++) {
      float chooseMat = DRAND;
      vec3 center(a + 0.9 * DRAND, 0.2, b + 0.9 * DRAND);
      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
        if (chooseMat < 0.8)  // diffuse
          objects.Add(new Sphere(center, 0.2, new Lambertian(vec3(DRAND * DRAND, DRAND * DRAND,DRAND * DRAND))));
        else if (chooseMat < 0.95)  // metal
          objects.Add(new Sphere(
              center, 0.2, new Metal(vec3(0.5 * (1 + DRAND * DRAND), 0.5 * (1 + DRAND * DRAND), 0.5 * (1 + DRAND * DRAND)), 0.3 * DRAND)));
        else
          objects.Add(new Sphere(center, 0.2, new Dielectric(1.5)));
      }
    }
  }

  objects.Add(new Sphere(vec3(0, 1, -1), 1, new Dielectric(1.5)));
  objects.Add(
      new Sphere(vec3(-4, 1, -1), 1, new Lambertian(vec3(0.8, 0.8, 0.0))));
  objects.Add(
      new Sphere(vec3(4, 0, -1), 1.5, new Metal(vec3(0.8, 0.6, 0.2), 0.1)));
}
#include <thread>
int main() {
	auto begin = std::chrono::steady_clock::now();
  //	I64vec1 sss(3, 3);
	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
  float w = 300, h = 200;
  int samples = 8;
  uint8_t *data1 = new uint8_t[w * h * 3];


  


  
  // HitableList *world = new HitableList();
  ///* float R = cosf(3.14 / 4);
  // world->Add(
  //     new Sphere(vec3(0, 0, -1),0.5, new Lambertian(vec3(0.0, 0.0, 1))));
  // world->Add(
  //         new Sphere(vec3(-1, 0, -1), 0.5, new Lambertian(vec3(1.0, 0.0,
  //         1))));
  // */

  ///*world->Add(
  //    new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.8, 0.3, 0.3))));
  // world->Add(new Sphere(vec3(0, -100.5, -1), 100,
  //                      new Lambertian(vec3(0.8, 0.8, 0.0))));
  // world->Add(
  //    new Sphere(vec3(1, 0, -1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.1)));*/
  // world->Add(new Sphere(vec3(-1, 0, -1), 0.5, new Dielectric(1.5)));
  // world->Add(new Sphere(vec3(-1, 0, -1), -0.45, new Dielectric(1.5)));
  RandomScene();
  const vec3 eye(13, 3, 5);
  const vec3 lookAt(0, 0, -1);
  float distToFocus = (eye - lookAt).length();
  float aperture = 0.0;

  Camera cam(eye, lookAt, vec3(0, 1, 0), 35.0f, float(w) / float(h), aperture,
             distToFocus);
#if 1
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      vec3 col(0);
      for (int s = 0; s < samples; s++) {
        float k = ((float)std::rand() / RAND_MAX);
        const float u = float(x + k) / w;
        const float v = float(y + k) / h;
        Ray r = cam.GetRay(u, v);
        col += color(r, &objects, 0);
      }
      col /= float(samples);
      const int pos = y * w * 3 + x * 3;
      data1[pos + 0] = uint8(255 * sqrtf(col.x));
      data1[pos + 1] = uint8(255 * sqrtf(col.y));
      data1[pos + 2] = uint8(255 * sqrtf(col.z));
    }
  }
#endif
  stbi_flip_vertically_on_write(1);
  stbi_write_png("f1.png", w, h, 3, data1, w * 3);
  auto end = std::chrono::steady_clock::now();
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << std::endl;
}
