#pragma once
#include <stdint.h>
#include <mutex>
#include <thread>
#include "Camera.h"
#include "Scene.h"
#include "Material.h"

#include "Image.h"
namespace StellarTrace {
	
struct TileParam {
  TileParam() {}
  TileParam(uint16_t _x , uint16_t _y,uint16_t _width , uint16_t _height) 
  {
	  x = _x;
	  y = _y;
	  width = _width;
	  height = _height;
  
  }
 /* TileParam(TileParam&& p) noexcept {
    x = p.x;
    y = p.y;
    width = p.width;
    height = p.height;
  }
  TileParam(const TileParam& p) noexcept {
    x = p.x;
    y = p.y;
    width = p.width;
    height = p.height;
  }

  void operator=(const TileParam& p) noexcept {
    x = p.x;
    y = p.y;
    width = p.width;
    height = p.height;
  }*/

  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
};

class Renderer {
 public:
  Renderer(uint32_t width, uint32_t height, uint16_t sample,
           uint8_t numThread);
  ~Renderer();
  void Render( Camera* camera, Scene* scene,const std::string& fileName);

 private:
	 void Test(Camera* c, Scene* scene) {};
  void QueueTask( Camera* camera, Scene* scene);

  void ColorTile( Camera* camera, Scene* scene, const TileParam& tparam);
  vec3 Color(const Ray& r, HitableList* world, int depth) const noexcept;

 private:
  std::vector<std::thread> Threads;
  uint8_t NumThread;
  uint16_t Width, Height;
  uint32_t Samples;
  std::mutex DataMutex;
  std::vector<TileParam> Tiles;
  Image* Img;
};
}  // namespace StellarTrace
