#pragma once
#include "../Core.h"
#include "../math/Vector3f.h"
namespace StellarTrace {
	// This is a row-major matrix; 
	class Matrix4f {
	public:
		float m[4][4];

		Matrix4f() {};

		Matrix4f(float a00, float a01, float a02, float a03, float a10, float a11,
			float a12, float a13, float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33) {
			m[0][0] = a00;
			m[0][1] = a01;
			m[0][2] = a02;
			m[0][3] = a03;
			m[1][0] = a10;
			m[1][1] = a11;
			m[1][2] = a12;
			m[1][3] = a13;
			m[2][0] = a20;
			m[2][1] = a21;
			m[2][2] = a22;
			m[2][3] = a23;
			m[3][0] = a30;
			m[3][1] = a31;
			m[3][2] = a32;
			m[3][3] = a33;
		}

		inline void initIdentity() {
			m[0][0] = 1.0f;
			m[0][1] = 0.0f;
			m[0][2] = 0.0f;
			m[0][3] = 0.0f;
			m[1][0] = 0.0f;
			m[1][1] = 1.0f;
			m[1][2] = 0.0f;
			m[1][3] = 0.0f;
			m[2][0] = 0.0f;
			m[2][1] = 0.0f;
			m[2][2] = 1.0f;
			m[2][3] = 0.0f;
			m[3][0] = 0.0f;
			m[3][1] = 0.0f;
			m[3][2] = 0.0f;
			m[3][3] = 1.0f;
		}

		Matrix4f transpose() const;
		operator const float*() const { 
			
			return (&m[0][0]); }
		inline Matrix4f operator*(const Matrix4f& right) const;
		// inline Matrix4f operator*(const Vector4f& v) const;
		float determinant()const;
		Matrix4f& inverse();
		Matrix4f& makePerspectiveProjection(const float znear , const float zfar ,const float width , const float height,const  float FOV );
		Matrix4f& makeTranslate( const vec3& vec3);
		Matrix4f& makeRotateTransform(const vec3& vec3);
		Matrix4f& makeCameraTransform(const vec3& pos , vec3& target,  vec3& up);
		Matrix4f& makeScale(const  vec3& vec3);
		
		
		/*Matrix4f& operator=(const Matrix4f& mat) {
	
			std::copy(mat.m, mat.m + sizeof(float) * 16, m[0][0]);
			return *this;
		}*/
				
	
		//const matrix
	};

	

	using mat4f = Matrix4f;


}
