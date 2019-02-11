
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <thread>
#include "Camera.h"
#include "Core.h"
#include "Dielectric.h"
#include "Hitable.h"
#include "HitableList.h"
#include "Lambertian.h"
#include "Math/Vector3f.h"
#include "Metal.h"
#include "Ray.h"
#include "Renderer.h"
#include "Sphere.h"
#include "Timer.h"
//#include <intrin.h>

// simd
// https://stackoverflow.com/questions/11228855/header-files-for-x86-simd-intrinsics
using namespace StellarTrace;

#define DRAND (float)std::rand() / RAND_MAX
Scene scene;
void RandomScene() {
  const int c = 10;
  scene.Add(new Sphere(vec3(0, -1000, 0), 1000, new Lambertian(vec3(0.5))));
  int i = 1;
  for (int a = -c; a < c; a++) {
    for (int b = -c; b < c; b++) {
      float chooseMat = DRAND;
      vec3 center(a + 0.9 * DRAND, 0.35, b + 0.9 * DRAND);
      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
        if (chooseMat < 0.4)  // diffuse
          scene.Add(new Sphere(center, center.y,
                               new Lambertian(vec3(DRAND * DRAND, DRAND * DRAND,
                                                   DRAND * DRAND))));
        else if (chooseMat < 0.7)  // metal
          scene.Add(new Sphere(center, center.y*DRAND,
                               new Metal(vec3(0.5 * (1 + DRAND * DRAND),
                                              0.5 * (1 + DRAND * DRAND),
                                              0.5 * (1 + DRAND * DRAND)),
                                         0.7 * DRAND*DRAND)));
        else
          scene.Add(new Sphere(center, center.y, new Dielectric(1.5)));
      }
    }
  }

  scene.Add(new Sphere(vec3(0, 1, -1), 1, new Lambertian(vec3(66.0f/255.0, 134.0/255.0, 244.0/255.0))));
  scene.Add(
      new Sphere(vec3(-4, 1, -1), -0.7, new Dielectric(1.3)));
  scene.Add(
      new Sphere(vec3(4, 0, -1), 1.5, new Metal(vec3(0.8, 0.6, 0.2), 0.1)));
}

int main() {
  
  int w = 1024, h = 512;
  int samples = 64;
  
  RandomScene();
  const vec3 eye(10, 3, 5);
  const vec3 lookAt(0, 0, -1);
  float distToFocus = (eye - lookAt).length();
  float aperture = 0.0;

  Camera cam(eye, lookAt, vec3(0, 1, 0), 35.0f, float(w) / float(h), aperture,
             distToFocus);

  Renderer renderer(w, h, samples, 0);
  TIME_IT(renderer.Render(&cam, &scene, "f1Threading.png"))

}
