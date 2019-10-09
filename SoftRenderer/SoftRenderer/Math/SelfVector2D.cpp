#include "SelfVector2D.h"
#include "SelfMaths.h"

void _Vector2D::Set(float x, float y)
{
	_x = x;
	_y = y;
}

void _Vector2D::SetX(float x)
{
	_x = x;
}

void _Vector2D::SetY(float y)
{
	_y = y;
}

float _Vector2D::GetX() const
{
	return _x;
}

float _Vector2D::GetY() const
{
	return _y;
}

void _Vector2D::Normalized()
{
	float len = GetLength();
	if (FLT_EQUAL(1.0f, len) || FLT_IS_ZERO(len))
	{
		return;
	}

	float factor = 1.0f / len;
	_x *= factor;
	_y *= factor;
}

float _Vector2D::GetLength() const
{
	return (float)sqrt((_x * _x) + (_y * _y));
}

_Vector2D _Vector2D::GetNormalized() const
{
	_Vector2D result(*this);
	result.Normalized();
	return result;
}

_Vector2D _Vector2D::Lerp(const _Vector2D& v2, float factor) const
{
	return (*this) * (1.0f - factor) + v2 * factor;
}

void _Vector2D::operator-=(const _Vector2D& v2)
{
	_x -= v2._x;
	_y -= v2._y;
}

_Vector2D _Vector2D::operator-() const
{
	return _Vector2D(-_x, -_y);
}

void _Vector2D::operator/=(const float v)
{
	if (FLT_IS_ZERO(v))
	{
		return;
	}
	_x /= v;
	_y /= v;
}

void _Vector2D::operator*=(const float v)
{
	_x *= v;
	_y *= v;
}

_Vector2D _Vector2D::operator*(const float v) const
{
	return _Vector2D(_x * v, _y * v);
}

_Vector2D _Vector2D::operator*(const _Vector2D& v2)
{
	return _Vector2D(_x * v2.GetX(), _y * v2.GetY());
}

bool _Vector2D::operator!=(const _Vector2D& v2) const
{
	return !((*this) == v2);
}

bool _Vector2D::operator==(const _Vector2D& v2) const
{
	return (FLT_EQUAL(_x, v2._x) && FLT_EQUAL(_y, v2._y));
}

_Vector2D _Vector2D::operator/(const float v) const
{
	if (FLT_IS_ZERO(v))
	{
		return _Vector2D(0.0f, 0.0f);
	}
	return _Vector2D(_x / v, _y / v);
}

_Vector2D _Vector2D::operator+(const _Vector2D& v2) const
{
	return _Vector2D(_x + v2._x, _y + v2._y);
}

_Vector2D _Vector2D::operator+() const
{
	return *this;
}

float _Vector2D::Dot(const _Vector2D& v2)const
{
	return (float)(_x * v2._x + _y * v2._y);
}

_Vector2D _Vector2D::operator-(const _Vector2D& v2) const
{
	return _Vector2D(_x - v2._x, _y - v2._y);
}

void _Vector2D::operator+=(const _Vector2D& v2)
{
	_x += v2._x;
	_y += v2._y;
}

_Vector2D operator*(float factor, const _Vector2D& v2)
{
	return _Vector2D(factor * v2._x, factor * v2._y);
}