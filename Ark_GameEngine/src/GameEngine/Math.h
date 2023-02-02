#pragma once
#include <math.h>

namespace Ark {
	struct vector3D {
		float x, y, z;

		vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
		vector3D(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}
	};

	struct vector2D {
		float x, y;

		vector2D() : x(0.0f), y(0.0f){}
		vector2D(float p_x, float p_y) : x(p_x), y(p_y) {}
	};

	struct matrix4x4 {

		union {
			struct {
				float
					m11, m21, m31, m41,
					m12, m22, m32, m42,
					m13, m23, m33, m43,
					m14, m24, m34, m44;
			};

			struct {
				float m_array[4][4];
			};
		};

		float* operator[](unsigned int id) {
			return &(reinterpret_cast<float*>(this)[id * 4]);
		}

		matrix4x4() : m_array{ 0 } {}
		matrix4x4(float p_11, float p_21, float p_31, float p_41,
			float p_12, float p_22, float p_32, float p_42,
			float p_13, float p_23, float p_33, float p_43,
			float p_14, float p_24, float p_34, float p_44) :
			m11(p_11), m21(p_21), m31(p_31), m41(p_41),
			m12(p_12), m22(p_22), m32(p_32), m42(p_42),
			m13(p_13), m23(p_23), m33(p_33), m43(p_43),
			m14(p_14), m24(p_24), m34(p_34), m44(p_44) {}

		void SetIdentity() {
			matrix4x4 t_mtx = matrix4x4();
			t_mtx[0][0] = t_mtx[1][1] = t_mtx[2][2] = t_mtx[3][3] = 1.0f;

		}
	};
}