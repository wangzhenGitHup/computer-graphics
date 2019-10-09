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
	if (FLT_EQUAL(1.0f, len) || FLT_IS_ZERO(len))
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

float _Vector3D::GetSquaredLength() const
{
	return (float)((_x * _x) + (_y * _y) + (_z * _z));
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

_Vector3D _Vector3D::operator+(const _Vector3D& v3) const
{
	return _Vector3D(_x + v3._x, _y + v3._y, _z + v3._z);
}

_Vector3D _Vector3D::operator+() const
{
	return *this;
}

float _Vector3D::Dot(const _Vector3D& v3)const
{
	return (float)(_x * v3._x + _y * v3._y + _z * v3._z);
}

_Vector3D _Vector3D::Cross(const _Vector3D& vec)const
{
	float v1, v2, v3;
	v1 = _y * vec._z - _z * vec._y;
	v2 = _z * vec._x - _x * vec._z;
	v3 = _x * vec._y - _y * vec._x;

	return _Vector3D(v1, v2, v3);
}

void _Vector3D::RotateX(double angle)
{
	(*this) = GetRotatedX(angle);
}

_Vector3D _Vector3D::GetRotatedX(double angle) const
{
	if (FLT_IS_ZERO(angle))
	{
		return *this;
	}
	//推导过程见 矩阵
	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return _Vector3D(_x, _y * cosAngle - _z * sinAngle, _y * sinAngle + _z * cosAngle);
}

void _Vector3D::RotateY(double angle)
{
	(*this) = GetRotatedY(angle);
}

_Vector3D _Vector3D::GetRotatedY(double angle) const
{
	if (FLT_IS_ZERO(angle))
	{
		return *this;
	}

	//推导过程见 矩阵
	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return _Vector3D(_x * cosAngle + _z * sinAngle, _y, _x * sinAngle + _z * cosAngle);
}

void _Vector3D::RotateZ(double angle)
{
	(*this) = GetRotatedZ(angle);
}

_Vector3D _Vector3D::GetRotatedZ(double angle) const
{
	if (FLT_IS_ZERO(angle))
	{
		return *this;
	}

	//推导过程见 矩阵
	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);

	return _Vector3D(_x * cosAngle - _y * sinAngle, _x * sinAngle + _y * cosAngle, _z);
}

void _Vector3D::RotateAxis(double angle, const _Vector3D& axis)
{
	(*this) = GetRotatedAxis(angle, axis);
}

_Vector3D _Vector3D::GetRotatedAxis(double angle, const _Vector3D& axis) const
{
	if (FLT_IS_ZERO(angle))
	{
		return *this;
	}
	//推导过程见矩阵绕任意轴旋转
	_Vector3D u = axis.GetNormalized();
	_Vector3D rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);
	float oneMinusCosAngle = 1.0f - cosAngle;

	rotMatrixRow0._x = u._x * u._x + cosAngle * (1 - u._x * u._x);
	rotMatrixRow0._y = u._x * u._y * oneMinusCosAngle - sinAngle * u._z;
	rotMatrixRow0._z = u._x * u._z * oneMinusCosAngle + sinAngle * u._y;

	rotMatrixRow1._x = u._x * u._y * oneMinusCosAngle + sinAngle * u._z;
	rotMatrixRow1._y = u._y * u._y + cosAngle * (1 - u._y * u._y);
	rotMatrixRow1._z = u._y * u._z * oneMinusCosAngle - sinAngle * u._x;

	rotMatrixRow2._x = u._x * u._z * oneMinusCosAngle - sinAngle * u._y;
	rotMatrixRow2._y = u._y * u._z * oneMinusCosAngle + sinAngle * u._x;
	rotMatrixRow2._z = u._z * u._z + cosAngle * (1 - u._z * u._z);

	return _Vector3D(rotMatrixRow0.Dot(rotMatrixRow0),
		rotMatrixRow1.Dot(rotMatrixRow1),
		rotMatrixRow2.Dot(rotMatrixRow2));
}

void _Vector3D::PackTo01()
{
	(*this) = GetPackedTo01();
}

_Vector3D _Vector3D::GetPackedTo01() const
{
	_Vector3D tmp(*this);
	tmp.Normalized();
	tmp = tmp * 0.5f + _Vector3D(0.5f, 0.5f, 0.5f);
	return tmp;
}

bool _Vector3D::operator!=(const _Vector3D& v3) const
{
	return !((*this) == v3);
}

bool _Vector3D::operator==(const _Vector3D& v3) const
{
	if (FLT_EQUAL(_x, v3.GetX()) && FLT_EQUAL(_y, v3.GetY()) && FLT_EQUAL(_z, v3.GetZ()))
	{
		return true;
	}

	return false;
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
	_x -= v3._x;
	_y -= v3._y;
	_z -= v3._z;
}

void _Vector3D::operator+=(const _Vector3D& v3)
{
	_x += v3._x;
	_y += v3._y;
	_z += v3._z;
}

_Vector3D operator*(float v, const _Vector3D& v3)
{
	return v3 * v;
}