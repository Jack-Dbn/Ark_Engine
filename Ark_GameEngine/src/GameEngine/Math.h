#pragma once
#include <math.h>
#define PI_F 3.1415927f

namespace Ark {	

	//Defines a 3D vector
	struct vector3D {
		float x, y, z;

		vector3D() : x(0.0f), y(0.0f), z(0.0f) {}//Init default values as 0.0f
		vector3D(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z) {}//Allow init values to be specified.
	};

	//Defines a 2D vector
	struct vector2D {
		float x, y;

		vector2D() : x(0.0f), y(0.0f){}//Init default values as 0.0f
		vector2D(float p_x, float p_y) : x(p_x), y(p_y) {}//Allow init values to be specified.
	};

	//Define a 4x4 matrix
	struct matrix4x4 {

		//A matrix can be considered as a 2D array and 16 individual elements.
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

		//Allows matrix to be indexed like an 2d array.
		float* operator[](unsigned int id) {
			return &(reinterpret_cast<float*>(this)[id * 4]);
		}

		matrix4x4() : m_array{ 0 } {}//Init default values as 0
		matrix4x4(float p_11, float p_21, float p_31, float p_41,
			float p_12, float p_22, float p_32, float p_42,
			float p_13, float p_23, float p_33, float p_43,
			float p_14, float p_24, float p_34, float p_44) :
			m11(p_11), m21(p_21), m31(p_31), m41(p_41),
			m12(p_12), m22(p_22), m32(p_32), m42(p_42),
			m13(p_13), m23(p_23), m33(p_33), m43(p_43),
			m14(p_14), m24(p_24), m34(p_34), m44(p_44) {}//Allow starting values to be specified.

		//Allow identity matrix instances to be created.
		matrix4x4(char initSymb) : m_array{ 0 } {
			if (initSymb == 'i') {
				m11 = m22 = m33 = m44 = 1.0f;
			}			
		}

		//Matrix multiplication
		inline matrix4x4 operator*(matrix4x4 A) {

			matrix4x4 returnMtx;

			//Iterate through rows.
			for (int i = 0; i < 4; i++) {
				//Iterate through columns.
				for (int j = 0; j < 4; j++) {

					returnMtx[i][j] = 0.0f;

					for (int k = 0; k < 4; k++) {
						returnMtx[i][j] += this->m_array[i][k] * A[k][j];
					}
				}
			}

			return returnMtx;
		}

		//Return a translate matrix.
		static matrix4x4 TranslateMtx(float x, float y, float z) {

			matrix4x4 returnMtx = {
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f};

			return returnMtx;
		}

		//Return a rotate matrix around x axis (pitch).
		static matrix4x4 RotateXmtx(float deg) {

			float radVal = (PI_F / 180.0f);

			float cosVal = cosf(deg * radVal);
			float sinVal = sinf(deg * radVal);

			matrix4x4 returnMtx = {
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, cosVal, -sinVal, 0.0f,
				0.0f, sinVal, cosVal, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };

			return returnMtx;
		}

		//Return a rotate matrix around y axis (yaw).
		static matrix4x4 RotateYmtx(float deg) {
			
			float radVal = (PI_F / 180.0f);

			float cosVal = cosf(deg * radVal);
			float sinVal = sinf(deg * radVal);

			matrix4x4 returnMtx = {
				cosVal, 0.0f, sinVal, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				-sinVal, 0.0f, cosVal, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };

			return returnMtx;
		}

		//Return a rotate matrix around z axis (roll).
		static matrix4x4 RotateZmtx(float deg) {
			
			float radVal = (PI_F / 180.0f);

			float cosVal = cosf(deg * radVal);
			float sinVal = sinf(deg * radVal);

			matrix4x4 returnMtx = {
				cosVal, sinVal, 0.0f, 0.0f,
				-sinVal, cosVal, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f };

			return returnMtx;
		}

		//Return a scale matrix.
		static matrix4x4 ScaleMtx(float x, float y, float z) {
			matrix4x4 returnMtx('i');

			returnMtx[0][0] = x;
			returnMtx[1][1] = y;
			returnMtx[2][2] = z;

			return returnMtx;
		}
	};

	//Define vertex data.
	struct vertex {
		vector3D pos;//Position of vertex.
		vector3D normal;//The direction the surface faces.
		vector2D texCoord;//Texture coordinates.
	};
}