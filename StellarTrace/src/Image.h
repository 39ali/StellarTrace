#pragma once
#include <stdint.h>
#include "Math\Vector3f.h"
#include <string>
namespace StellarTrace {
class Image {
 public:
  Image(const uint16_t w, const uint16_t h):W(w),H(h) { Data = new uint8_t[w * h * 3]; }

  inline void WritePixel(const uint16_t x, const uint16_t y,
                         const vec3& col) noexcept {
	  const int pos = y * W * 3 + x * 3;
	  Data[pos + 0] = uint8_t(255.99 * sqrtf(col.x));
	  Data[pos + 1] = uint8_t(255.99 * sqrtf(col.y));
	  Data[pos + 2] = uint8_t(255.99 * sqrtf(col.z));
  }
   void Save(const std::string& name)const noexcept;

 private:
  uint8_t* Data = nullptr;
  uint16_t W, H;
};

}  // namespace StellarTrace
