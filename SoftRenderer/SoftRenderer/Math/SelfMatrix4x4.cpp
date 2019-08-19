#include "SelfMatrix4x4.h"
#include "SelfMaths.h"
#include <memory.h>

Matrix4x4::Matrix4x4()
{
	LoadIdentity();
}

Matrix4x4::Matrix4x4(float m0, float m1, float m2, float m3, 
	float m4, float m5, float m6, float m7, 
	float m8, float m9, float m10, float m11, 
	float m12, float m13, float m14, float m15)
{
	_elements[0] = m0;
	_elements[1] = m1;
	_elements[2] = m2;
	_elements[3] = m3;
	_elements[4] = m4;
	_elements[5] = m5;
	_elements[6] = m6;
	_elements[7] = m7;
	_elements[8] = m8;
	_elements[9] = m9;
	_elements[10] = m10;
	_elements[11] = m11;
	_elements[12] = m12;
	_elements[13] = m13;
	_elements[14] = m14;
	_elements[15] = m15;
}

Matrix4x4::Matrix4x4(const float* v)
{
	memcpy(_elements, v, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix)
{
	memcpy(_elements, matrix._elements, 16 * sizeof(float));
}

void Matrix4x4::LoadIdentity()
{
	memset(_elements, 0, 16 * sizeof(float));
	_elements[0] = 1.0f;
	_elements[5] = 1.0f;
	_elements[10] = 1.0f;
	_elements[15] = 1.0f;
}
