#include "SelfVector4D.h"
#include "SelfMaths.h"

void _Vector4D::Set(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

void _Vector4D::SetX(float x)
{
	_x = x;
}

void _Vector4D::SetY(float y)
{
	_y = y;
}

void _Vector4D::SetZ(float z)
{
	_z = z;
}

void _Vector4D::SetW(float w)
{
	_w = w;
}

void _Vector4D::LoadZero()
{
	_x = _y = _z = _w = 0.0f;
}

void _Vector4D::LoadOne()
{
	_x = _y = _z = _w = 1.0f;
}

_Vector4D _Vector4D::Lerp(const _Vector4D& v4, float factor) const
{
	return (*this) * (1.0f - factor) + v4 * factor;
}

void _Vector4D::Normalized()
{
	float len = GetLength();
	if (FLT_EQUAL(1.0f, len) || FLT_IS_ZERO(len))
	{
		return;
	}

	float factor = 1.0f / len;
	_x *= factor;
	_y *= factor;
	_z *= factor;
}

_Vector3D _Vector4D::GetNormalized() const
{
	_Vector3D result(_x, _y, _z);
	result.Normalized();
	return result;
}

float _Vector4D::GetLength() const
{
	return (float)sqrt(_x * _x + _y * _y + _z * _z);
}

float _Vector4D::GetSquaredLength() const
{
	return (float)(_x * _x + _y * _y + _z * _z);
}

void _Vector4D::RotateX(double angle)
{
	(*this) = GetRotateX(angle);
}

_Vector4D _Vector4D::GetRotateX(double angle) const
{
	_Vector3D v3d(_x, _y, _z);
	v3d.RotateX(angle);
	return _Vector4D(v3d.GetX(), v3d.GetY(), v3d.GetZ(), _w);
}

void _Vector4D::RotateY(double angle)
{
	(*this) = GetRotateY(angle);
}

_Vector4D _Vector4D::GetRotateY(double angle) const
{
	_Vector3D v3d(_x, _y, _z);
	v3d.RotateY(angle);
	return _Vector4D(v3d.GetX(), v3d.GetY(), v3d.GetZ(), _w);
}

void _Vector4D::RotateZ(double angle)
{
	(*this) = GetRotateZ(angle);
}

_Vector4D _Vector4D::GetRotateZ(double angle) const
{
	_Vector3D v3d(_x, _y, _z);
	v3d.RotateZ(angle);
	return _Vector4D(v3d.GetX(), v3d.GetY(), v3d.GetZ(), _w);
}

void _Vector4D::RotateAxis(double angle, const _Vector3D& axis)
{
	(*this) = GetRotateAxis(angle, axis);
}

_Vector4D _Vector4D::GetRotateAxis(double angle, const _Vector3D& axis) const
{
	_Vector3D v3d(_x, _y, _z);
	v3d.RotateAxis(angle, axis);
	return _Vector4D(v3d.GetX(), v3d.GetY(), v3d.GetZ(), _w);
}

_Vector4D _Vector4D::operator+(const _Vector4D& v4) const
{
	return _Vector4D(_x + v4._x, _y + v4._y, _z + v4._z, _w + v4._w);
}

_Vector4D _Vector4D::operator+() const
{
	return (*this);
}

bool _Vector4D::operator==(const _Vector4D& v4) const
{
	return (FLT_EQUAL(_x, v4._x) && FLT_EQUAL(_y, v4._y) && FLT_EQUAL(_z, v4._z) && FLT_EQUAL(_w, v4._w));
}

bool _Vector4D::operator!=(const _Vector4D& v4) const
{
	return !((*this) == v4);
}

_Vector4D _Vector4D::operator-(const _Vector4D& v4) const
{
	return _Vector4D(_x - v4._x, _y - v4._y, _z - v4._z, _w - v4._w);
}

_Vector4D _Vector4D::operator-() const
{
	return _Vector4D(-_x, -_y, -_z, -_w);
}

_Vector4D _Vector4D::operator*(const float v) const
{
	return _Vector4D(v * _x, v * _y, v * _z, v * _w);
}

void _Vector4D::operator*=(const float v)
{
	_x *= v;
	_y *= v;
	_z *= v;
	_w *= v;
}

void _Vector4D::operator/=(const float v)
{
	if (FLT_IS_ZERO(v))
	{
		return;
	}

	_x /= v;
	_y /= v;
	_z /= v;
	_w /= v;
}

void _Vector4D::operator-=(const _Vector4D& v4)
{
	_x -= v4._x;
	_y -= v4._y;
	_z -= v4._z;
	_w -= v4._w;
}

void _Vector4D::operator+=(const _Vector4D& v4)
{
	_x += v4._x;
	_y += v4._y;
	_z += v4._z;
	_w += v4._w;
}

_Vector4D _Vector4D::operator/(const float v) const
{
	if (FLT_IS_ZERO(v))
	{
		return _Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
	}

	return _Vector4D(_x / v, _y / v, _z / v, _w / v);
}

_Vector4D operator*(float factor, const _Vector4D& v4)
{
	return v4 * factor;
}

_Vector4D::operator _Vector3D()
{
	if (FLT_IS_ZERO(_w) || FLT_EQUAL(1.0f, _w))
	{
		return _Vector3D(_x, _y, _z);
	}

	return _Vector3D(_x / _w, _y / _w, _z / _w);
}

float _Vector4D::Dot(const _Vector4D& v4)const
{
	return(_x * v4._x + _y * v4._y + _z * v4._z + _w * v4._w);
}


