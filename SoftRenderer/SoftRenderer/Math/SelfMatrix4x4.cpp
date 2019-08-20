#include "SelfMatrix4x4.h"
#include "SelfVector4D.h"
#include "SelfVector3D.h"
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

void Matrix4x4::SetElement(int pos, float v)
{
	if (pos >= 0 && pos <= 15)
	{
		_elements[pos] = v;
	}
}

float Matrix4x4::GetElement(int pos) const
{
	if (pos >= 0 && pos <= 15)
	{
		return _elements[pos];
	}

	return 0.0f;
}

_Vector4D Matrix4x4::GetRow(int pos) const
{
	switch (pos)
	{
	case 0:
		return _Vector4D(_elements[0], _elements[4], _elements[8], _elements[12]);

	case 1:
		return _Vector4D(_elements[1], _elements[5], _elements[9], _elements[13]);

	case 2:
		return _Vector4D(_elements[2], _elements[6], _elements[10], _elements[14]);

	case 3:
		return _Vector4D(_elements[3], _elements[7], _elements[11], _elements[15]);

	default:
		return _Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

_Vector4D Matrix4x4::GetColumn(int pos) const
{
	switch (pos)
	{
	case 0:
		return _Vector4D(_elements[0], _elements[1], _elements[2], _elements[3]);

	case 1:
		return _Vector4D(_elements[4], _elements[5], _elements[6], _elements[7]);

	case 2:
		return _Vector4D(_elements[8], _elements[9], _elements[10], _elements[11]);

	case 3:
		return _Vector4D(_elements[12], _elements[13], _elements[14], _elements[15]);

	default:
		return _Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void Matrix4x4::LoadZero()
{
	memset(_elements, 0, 16 * sizeof(float));
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& matrix) const
{
	return Matrix4x4(_elements[0] + matrix._elements[0],
		_elements[1] + matrix._elements[1], 
		_elements[2] + matrix._elements[2], 
		_elements[3] + matrix._elements[3], 
		_elements[4] + matrix._elements[4], 
		_elements[5] + matrix._elements[5], 
		_elements[6] + matrix._elements[6], 
		_elements[7] + matrix._elements[7], 
		_elements[8] + matrix._elements[8], 
		_elements[9] + matrix._elements[9], 
		_elements[10] + matrix._elements[10], 
		_elements[11] + matrix._elements[11], 
		_elements[12] + matrix._elements[12], 
		_elements[13] + matrix._elements[13], 
		_elements[14] + matrix._elements[14], 
		_elements[15] + matrix._elements[15] );
}

Matrix4x4 Matrix4x4::operator+() const
{
	return (*this);
}

void Matrix4x4::RotateVector3D(_Vector3D& v3) const
{
	v3 = GetRotatedVector3D(v3);
}

void Matrix4x4::InverseRotateVector3D(_Vector3D& v3) const
{
	v3 = GetInverseRotatedVector3D(v3);
}

_Vector3D Matrix4x4::GetRotatedVector3D(const _Vector3D& v3) const
{
	return _Vector3D(
		_elements[0] * v3.GetX() + _elements[4] * v3.GetY() + _elements[8] * v3.GetZ(),
		_elements[1] * v3.GetX() + _elements[5] * v3.GetY() + _elements[9] * v3.GetZ(), 
		_elements[2] * v3.GetX() + _elements[6] * v3.GetY() + _elements[10] * v3.GetZ()
		);
}

_Vector3D Matrix4x4::GetInverseRotatedVector3D(const _Vector3D& v3) const
{
	//旋转变化的逆矩阵直接转置就行了
	return _Vector3D(
		_elements[0] * v3.GetX() + _elements[1] * v3.GetY() + _elements[2] * v3.GetZ(),
		_elements[4] * v3.GetX() + _elements[5] * v3.GetY() + _elements[6] * v3.GetZ(),
		_elements[8] * v3.GetX() + _elements[9] * v3.GetY() + _elements[10] * v3.GetZ()
		);
}

void Matrix4x4::TranslateVector3D(_Vector3D& v3) const
{
	v3 = GetTranslatedVector3D(v3);
}

void Matrix4x4::InverseTranslateVector3D(_Vector3D& v3) const
{
	v3 = GetInverseTranslatedVector3D(v3);
}

_Vector3D Matrix4x4::GetTranslatedVector3D(const _Vector3D& v3) const
{
	return _Vector3D(
		v3.GetX() + _elements[12], 
		v3.GetY() + _elements[13], 
		v3.GetZ() + _elements[14]
		);
}

_Vector3D Matrix4x4::GetInverseTranslatedVector3D(const _Vector3D& v3) const
{
	//平移变化的逆矩阵直接减去元素值
	return _Vector3D(
		v3.GetX() - _elements[12],
		v3.GetY() - _elements[13],
		v3.GetZ() - _elements[14]
		);
}

void Matrix4x4::Inverse()
{
	*this = GetInverse();
}

Matrix4x4 Matrix4x4::GetInverse() const
{
	Matrix4x4 result = GetInverseTranspose();
	result.Transpose();
	return result;
}

void Matrix4x4::Transpose()
{
	*this = GetTranspose();
}

Matrix4x4 Matrix4x4::GetTranspose() const
{
	//行列置换
	return Matrix4x4(
		_elements[0], _elements[4], _elements[8], _elements[12],
		_elements[1], _elements[5], _elements[9], _elements[13],
		_elements[2], _elements[6], _elements[10], _elements[14],
		_elements[3], _elements[7], _elements[11], _elements[15]
		);
}

void Matrix4x4::InverseTranspose()
{
	*this = GetInverseTranspose();
}

Matrix4x4 Matrix4x4::GetInverseTranspose()const
{
	Matrix4x4 result;
	//TODO:
}

void Matrix4x4::AffineInverse()
{
	*this = GetAffineInverse();
}

Matrix4x4 Matrix4x4::GetAffineInverse() const
{
	Matrix4x4 result;
	//TODO:
}

void Matrix4x4::AffineInverseTranspose()
{
	*this = GetAffineInverseTranspose();
}

Matrix4x4 Matrix4x4::GetAffineInverseTranspose()
{
	Matrix4x4 result;
	//TODO:
}

void Matrix4x4::SetTranslation(const _Vector3D& translation)
{
	LoadIdentity();
	SetTranslationPart(translation);
}

void Matrix4x4::SetScale(const _Vector3D& v3)
{
	LoadIdentity();
	_elements[0] = v3.GetX();
	_elements[5] = v3.GetY();
	_elements[10] = v3.GetZ();
}

void Matrix4x4::SetUniformScale(const float factor)
{
	LoadIdentity();
	_elements[0] = _elements[5] = _elements[10] = factor;
}

void Matrix4x4::SetRotationAxis(const double angle, const _Vector3D& axis)
{
	LoadIdentity();
}

void Matrix4x4::SetRotationX(const double angle)
{
	LoadIdentity();
}

void Matrix4x4::SetRotationY(const double angle)
{
	LoadIdentity();
}

void Matrix4x4::SetRotationZ(const double angle)
{
	LoadIdentity();
}

void Matrix4x4::SetRotationEuler(const double angleX, const double angleY, const double angleZ)
{
	LoadIdentity();
}

void Matrix4x4::SetOrtho(float left, float right, float bottom, float top, float near, float far)
{

}

void Matrix4x4::SetPerspective(float fovy, float aspect, float near, float far)
{

}

void Matrix4x4::SetTranslationPart(const _Vector3D& v3)
{

}

void Matrix4x4::SetRotationPartEuler(const double angleX, const double angleY, const double angleZ)
{

}

void Matrix4x4::SetRotationPartEuler(const _Vector3D& v3)
{
	SetRotationPartEuler((double)v3.GetX(), (double)v3.GetY(), (double)v3.GetZ());
}

bool Matrix4x4::operator!=(const Matrix4x4& matrix) const
{
	return !((*this) == matrix);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& matrix) const
{
	return Matrix4x4(_elements[0] - matrix._elements[0],
		_elements[1] - matrix._elements[1],
		_elements[2] - matrix._elements[2],
		_elements[3] - matrix._elements[3],
		_elements[4] - matrix._elements[4],
		_elements[5] - matrix._elements[5],
		_elements[6] - matrix._elements[6],
		_elements[7] - matrix._elements[7],
		_elements[8] - matrix._elements[8],
		_elements[9] - matrix._elements[9],
		_elements[10] - matrix._elements[10],
		_elements[11] - matrix._elements[11],
		_elements[12] - matrix._elements[12],
		_elements[13] - matrix._elements[13],
		_elements[14] - matrix._elements[14],
		_elements[15] - matrix._elements[15]);
}

void Matrix4x4::operator-=(const Matrix4x4& matrix)
{
	(*this) = (*this) - matrix;
}

Matrix4x4 Matrix4x4::operator-() const
{
	Matrix4x4 result(*this);
	for (int i = 0; i < 16; i++)
	{
		result._elements[i] = -result._elements[i];
	}

	return result;
}

void Matrix4x4::operator/=(const float v)
{
	if (FLT_IS_ZERO(v))
	{
		return;
	}

	(*this) = (*this) / v;
}

_Vector4D Matrix4x4::operator*=(const _Vector4D& v4) const
{
	if (_elements[3] == 0.0f && 
		_elements[7] == 0.0f && 
		_elements[11] == 0.0f && 
		_elements[15] == 1.0f)
	{
		return _Vector4D(
				_elements[0] * v4.GetX() + _elements[4] * v4.GetY() + _elements[8] * v4.GetZ() + _elements[12] * v4.GetW(), 
				_elements[1] * v4.GetX() + _elements[5] * v4.GetY() + _elements[9] * v4.GetZ() + _elements[13] * v4.GetW(), 
				_elements[2] * v4.GetX() + _elements[6] * v4.GetY() + _elements[10] * v4.GetZ() + _elements[14] * v4.GetW(),
				v4.GetW()
			);
	}

	return _Vector4D(
		_elements[0] * v4.GetX() + _elements[4] * v4.GetY() + _elements[8] * v4.GetZ() + _elements[12] * v4.GetW(),
		_elements[1] * v4.GetX() + _elements[5] * v4.GetY() + _elements[9] * v4.GetZ() + _elements[13] * v4.GetW(),
		_elements[2] * v4.GetX() + _elements[6] * v4.GetY() + _elements[10] * v4.GetZ() + _elements[14] * v4.GetW(),
		_elements[3] * v4.GetX() + _elements[7] * v4.GetY() + _elements[11] * v4.GetZ() + _elements[15] * v4.GetW()
		);
}

void Matrix4x4::operator*=(const float v)
{
	(*this) = (*this) * v;
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	(*this) = (*this) * matrix;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix) const
{

}

Matrix4x4 Matrix4x4::operator*(const float v) const
{
	return Matrix4x4(_elements[0] * v,
		_elements[1] * v,
		_elements[2] * v,
		_elements[3] * v,
		_elements[4] * v,
		_elements[5] * v,
		_elements[6] * v,
		_elements[7] * v,
		_elements[8] * v,
		_elements[9] * v,
		_elements[10] * v,
		_elements[11] * v,
		_elements[12] * v,
		_elements[13] * v,
		_elements[14] * v,
		_elements[15] * v);
}

bool Matrix4x4::operator==(const Matrix4x4& matrix) const
{
	for (int i = 0; i < 16; i++)
	{
		if (_elements[i] != matrix._elements[i])
		{
			return false;
		}
	}

	return true;
}

Matrix4x4 Matrix4x4::operator/(const float v) const
{
	if (FLT_IS_ZERO(v) || 1.0f == v)
	{
		return (*this);
	}

	float factor = 1.0f / v;
	return (*this) * factor;
}

void Matrix4x4::operator+=(const Matrix4x4& matrix)
{
	(*this) = (*this) + matrix;
}

Matrix4x4 operator*(float factor, const Matrix4x4& matrix)
{
	return matrix * factor;
}