#include "SelfVector3D.h"
#include "SelfMaths.h"

void _Vector3D::Set(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void _Vector3D::SetX(float x)
{
	_x = x;
}

void _Vector3D::SetY(float y)
{
	_y = y;
}

void _Vector3D::SetZ(float z)
{
	_z = z;
}

void _Vector3D::LoadZero()
{
	_x = _y = _z = 0.0f;
}

void _Vector3D::LoadOne()
{
	_x = _y = _z = 1.0f;
}

void _Vector3D::Normalized()
{
	float len = GetLength();
	if (1 == len || 0 == len)
	{
		return;
	}

	float factor = 1.0f / len;
	_x *= factor;
	_y *= factor;
	_z *= factor;
}

float _Vector3D::GetLength() const
{
	return (float)sqrt((_x * _x) + (_y * _y) + (_z * _z));
}

_Vector3D _Vector3D::GetNormalized() const
{
	_Vector3D result(*this);
	result.Normalized();
	return result;
}

_Vector3D _Vector3D::Lerp(const _Vector3D& v3, float factor) const
{
	return (*this) * (1.0 - factor) + v3 * factor;
}

_Vector3D _Vector3D::QuadraticInterpolate(const _Vector3D& a, const _Vector3D& b, float factor)
{
	return (*this) * (1.0f - factor) * (1.0f - factor) + 2.0f * a * factor * (1.0 - factor) + b * factor * factor;
}

_Vector3D _Vector3D::operator+(const _Vector3D& v3) const
{
	return _Vector3D(_x + v3._x, _y + v3._y, _z + v3._z);
}

_Vector3D _Vector3D::operator+() const
{
	return *this;
}

float _Vector3D::Dot(const _Vector3D& a, const _Vector3D& b)
{
	return (float)(a._x * b._x + a._y * b._y + a._z * b._z);
}

_Vector3D _Vector3D::Cross(const _Vector3D& a, const _Vector3D& b)
{
	float v1, v2, v3;
	v1 = a._y * b._z - a._z * b._y;
	v2 = a._z * b._x - a._x * b._z;
	v3 = a._x * b._y - a._y * b._x;

	return _Vector3D(v1, v2, v3);
}

void _Vector3D::Add(const _Vector3D& src, _Vector3D& dst)
{
	dst._x += src._x;
	dst._y += src._y;
	dst._z += src._z;
}

void _Vector3D::Subtract(const _Vector3D& src, _Vector3D& dst)
{
	dst._x -= src._x;
	dst._y -= src._y;
	dst._z -= src._z;
}

_Vector3D _Vector3D::operator-(const _Vector3D& v3) const
{
	return _Vector3D(_x - v3._x, _y - v3._y, _z - v3._z);
}

_Vector3D _Vector3D::operator-() const
{
	return _Vector3D(-_x, -_y, -_z);
}

void _Vector3D::operator/=(const float v)
{
	if (FLT_IS_ZERO(v))
	{
		return;
	}

	_x /= v;
	_y /= v;
	_z /= v;
}

void _Vector3D::operator*=(const float v)
{
	_x *= v;
	_y *= v;
	_z *= v;
}

_Vector3D _Vector3D::operator*(const float v) const
{
	return _Vector3D(_x * v, _y * v, _z * v);
}

_Vector3D _Vector3D::operator/(const float v) const
{
	if (FLT_IS_ZERO(v))
	{
		return _Vector3D(0.0f, 0.0f, 0.0f);
	}

	return _Vector3D(_x / v, _y / v, _z / v);
}

void _Vector3D::operator-=(const _Vector3D& v3)
{

}

void _Vector3D::operator+=(const _Vector3D& v3)
{

}

_Vector3D operator*(float v, const _Vector3D& v3)
{
	return _Vector3D(v * v3._x, v * v3._y, v * v3._z);
}