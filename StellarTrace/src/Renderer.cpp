#include "Renderer.h"
#include <iostream>
#include <assert.h>
namespace StellarTrace {
	/// if numThread =0 > auto detect cores
Renderer::Renderer(uint32_t width, uint32_t height, uint16_t samples,
                   uint8_t numThread=0):Width(width),Height(height),Samples(samples)
{
	Img = new Image(width, height);
	if (numThread == 0) {
		unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
		if (concurentThreadsSupported <= 0)
			NumThread = 1;
		else
			NumThread = concurentThreadsSupported;
	}

}
Renderer::~Renderer() { delete Img; }
void Renderer::Render( Camera* camera,  Scene* scene, const std::string& FileName) {
	printf("Starting ... \n");

	uint16_t tileH = Height / NumThread;
	uint16_t sumOfHeight=0;
	for (uint8_t i = 0; i < NumThread; i++) 
	{
		uint16_t tileYPos = tileH * i;
		Tiles.emplace_back( 0,tileYPos,Width,tileH );
		sumOfHeight += tileH;
	}
	assert(sumOfHeight == Height); // something went horribly wrong;

	for (uint8_t i = 0; i < NumThread; i++)
		Threads.push_back(std::thread(&Renderer::QueueTask, this,camera,scene));

	for (uint8_t i = 0; i < NumThread; i++) {
		if (Threads[i].joinable())
			Threads[i].join();
	}
	printf("Saving...\n");
	Img->Save(FileName);
	printf("PNG Image Saved ! .\n");
}

void Renderer::QueueTask( Camera* camera,  Scene* scene) 
{
	size_t num;
	TileParam tparam;
	{
		std::lock_guard<std::mutex> lock(DataMutex);
		if (Tiles.empty())
		return;
		tparam = { Tiles.back() };
		num = Tiles.size();
		std::cout << "Current tile being rendered: " << num
			<< " Rendered by thread #: " << std::this_thread::get_id() << std::endl;
		Tiles.pop_back();
	}
	ColorTile(camera,scene,tparam);
	std::cout << "Finished  rendering tile: " << num<< std::endl;
}



void Renderer::ColorTile( Camera* camera,  Scene* scene,
	const TileParam& tparam) {

#if 1
	for (uint16_t y = tparam.y; y <  tparam.y+ tparam.height; y++) {
		for (uint16_t x = tparam.x; x <  tparam.x + tparam.width; x++) {
			vec3 col(0);
			Ray r;
			for (uint16_t s = 0; s < Samples; s++) {
				float k = ((float)std::rand() / RAND_MAX);
				const float u = float(x + k) / Width;
				const float v = float(y + k) / Height;
				Ray r = camera->GetRay(u, v);
				col += Color(r, &scene->Objects , 0);
			}
			col /= float(Samples);
			Img->WritePixel(x, y, col);
			
		}
	}
	#endif
	
}

vec3 Renderer::Color(const Ray& r, HitableList* world, int depth) const
    noexcept {
  HitRecord rec;

  if (world->Hit(r, 0.01, std::numeric_limits<float>::max(), rec)) {
    Ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.material->Scatter(r, rec, attenuation, scattered)) {
      return attenuation * Color(scattered, world, depth + 1);
    } else
      return vec3(0);
  }
  vec3 dir = r.Direction.normalize();
  // convert from -1 - +1 to 0-1
  float t = 0.5 * (dir.y + 1.0);
  return (1.0 - t) * vec3(1) + (t)*vec3(0.5, 0.7, 1.0);
}

}  // namespace StellarTrace
