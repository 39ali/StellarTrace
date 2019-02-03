#pragma once
#include "Vector3f.h"
#include "../Core.h"
namespace StellarTrace {
	class Color {
	public:
		Color(const vec3& color, float alpha) :data(color), alpha(alpha) {

		};
		inline  float operator[](uint32 index)const;
	private:
		vec3  data;
		float alpha;
	};




	inline  float Color::operator[](uint32 index)const {
		return data[index];
	}
}