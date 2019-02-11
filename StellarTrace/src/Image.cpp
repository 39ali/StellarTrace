#pragma once
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "../vendor/stb_image_write.h"
#include "Image.h"

namespace StellarTrace {

void Image::Save(const std::string& name) const noexcept {
   stbi_flip_vertically_on_write(1);
   stbi_write_png(name.c_str(), W, H, 3, Data, W * 3);
}

}  // namespace StellarTrace
