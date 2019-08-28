#include "Color.h"
#include "SelfMaths.h"

Color::Color()
{
	_r = _g = _b = _alpha = 0.0f;
}

Color::Color(const float* value)
{
	_r =* value;
	_g =* (value + 1);
	_b = *(value + 2);
	_alpha = *(value + 3);
}

Color::Color(const Color& clr)
{
	_r = clr._r;
	_g = clr._g;
	_b = clr._b;
	_alpha = clr._alpha;
}

Color::~Color()
{

}

void Color::Set(float r, float g, float b, float alpha /*= 0.0f*/)
{
	_r = r;
	_g = g;
	_b = b;
	_alpha = alpha;
}

void Color::SetR(float r)
{
	_r = r;
}

void Color::SetG(float g)
{
	_g = g;
}

void Color::SetB(float b)
{
	_b = b;
}

void Color::SetAlpha(float alpha)
{
	_alpha = alpha;
}

float Color::GetR() const
{
	return _r;
}

float Color::GetG() const
{
	return _g;
}

float Color::GetB() const
{
	return _b;
}

float Color::GetAlpha() const
{
	return _alpha;
}

void Color::ClampTo01()
{
	if (_r > 1.0f)
	{
		_r = 1.0f;
	}
	else if (_r < 0.0f)
	{
		_r = 0.0f;
	}

	if (_g > 1.0f)
	{
		_g = 1.0f;
	}
	else if (_g < 0.0f)
	{
		_g = 0.0f;
	}

	if (_b > 1.0f)
	{
		_b = 1.0f;
	}
	else if (_b < 0.0f)
	{
		_b = 0.0f;
	}

	if (_alpha > 1.0f)
	{
		_alpha = 1.0f;
	}
	else if (_alpha < 0.0f)
	{
		_alpha = 0.0f;
	}
}

void Color::SetBlack()
{
	_r = _g = _b = 0.0f;
	_alpha = 1.0f;
}

void Color::SetWhite()
{
	_r = _g = _b = _alpha = 1.0f;
}

void Color::SetGrey(float shade)
{
	_r = _g = _b = _alpha = shade;
}

Color Color::Lerp(const Color& clr, float factor)
{
	return (*this) * (1.0 - factor) + clr * factor;
}

Color Color::operator*=(const Color& clr)
{
	(*this) = (*this) * clr;
	return (*this);
}

Color Color::operator/=(const Color& clr)
{
	(*this) = (*this) / clr;
	return (*this);
}

Color Color::operator*=(const float v)
{
	(*this) = (*this) * v;
	return (*this);
}

Color Color::operator/=(const float v)
{
	(*this) = (*this) / v;
	return (*this);
}

Color Color::operator-(const Color& clr) const
{
	return Color(_r - clr._r, _g - clr._g, _b - clr._b, _alpha - clr._alpha);
}

Color Color::operator-() const
{
	return Color(_r, _g, _b, _alpha);
}

Color Color::operator*(const Color& clr) const
{
	return Color(_r * clr._r, _g * clr._g, _b * clr._b, _alpha * clr._alpha);
}

Color Color::operator*(const float v) const
{
	return Color(_r * v, _g * v, _b * v, _alpha * v);
}

Color Color::operator-=(const Color& clr)
{
	(*this) = (*this) - clr;
	return (*this);
}

Color Color::operator+=(const Color& clr)
{
	(*this) = (*this) + clr;
	return (*this);
}

Color Color::operator+() const
{
	return (*this);
}

bool Color::operator!=(const Color& clr) const
{
	return !((*this) == clr);
}

bool Color::operator==(const Color& clr) const
{
	if (FLT_EQUAL(_r, clr._r) &&
		FLT_EQUAL(_g, clr._g) && 
		FLT_EQUAL(_b, clr._b) && 
		FLT_EQUAL(_alpha, clr._alpha))
	{
		return true;
	}

	return false;
}

Color Color::operator/(const Color& clr) const
{
	return Color(_r / clr._r, _g / clr._g, _b / clr._b, _alpha / clr._alpha);
}

Color Color::operator/(const float v) const
{
	return Color(_r / v, _g / v, _b / v, _alpha / v);
}

Color Color::operator+(const Color& clr) const
{
	return Color(_r + clr._r, _g + clr._g, _b + clr._b, _alpha + clr._alpha);
}

Color operator*(float factor, const Color& clr)
{
	return Color(clr._r * factor, clr._g * factor, clr._b * factor, clr._alpha * factor);
}