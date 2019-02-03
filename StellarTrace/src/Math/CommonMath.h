#pragma once
namespace StellarTrace {
#define M_PI       3.14159265358979323846
	static float toRadian(const float x) {
		return (float)(M_PI*x / 180.0f);
	}

	static float toDegrees(const float x) {
		return (float)(x*180.0f / M_PI);
	}
}
