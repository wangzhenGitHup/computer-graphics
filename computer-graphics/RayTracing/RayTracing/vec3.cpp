#include "vec3.h"

vec3 operator + (const vec3& v1, const vec3& v2)
{
	return vec3(v1.m_vec[0] + v2.m_vec[0], 
		v1.m_vec[1] + v2.m_vec[1], 
		v1.m_vec[2] + v2.m_vec[2]);
}

vec3& vec3::operator -= (const vec3& v2)
{
	m_vec[0] -= v2.m_vec[0];
	m_vec[1] -= v2.m_vec[1];
	m_vec[2] -= v2.m_vec[2];
	return *this;
}

vec3 operator - (const vec3& v1, const vec3& v2)
{
	return vec3(v1.m_vec[0] - v2.m_vec[0], 
		v1.m_vec[1] - v2.m_vec[1], 
		v1.m_vec[2] - v2.m_vec[2]);
}

void vec3::Normalize()
{
	float k = 1.0 / sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]);
	m_vec[0] *= k;
	m_vec[1] *= k;
	m_vec[2] *= k;
}

std::istream& operator >> (std::istream& is, vec3& t)
{
	is >> t.m_vec[0] >> t.m_vec[1] >> t.m_vec[2];
	return is;
}

std::ostream& operator << (std::ostream& os, const vec3& t)
{
	os << t.m_vec[0] << "   " << t.m_vec[1] << "   " << t.m_vec[2];
	return os;
}

vec3 operator / (const vec3& v1, const vec3& v2)
{
	return vec3(v1.m_vec[0] / v2.m_vec[0],
		v1.m_vec[1] / v2.m_vec[1],
		v1.m_vec[2] / v2.m_vec[2]);
}

vec3 operator/(const vec3& v, float t)
{
	return vec3(v.m_vec[0] / t, v.m_vec[1] / t, v.m_vec[2] / t);
}

vec3& vec3::operator *= (const float t)
{
	m_vec[0] *= t;
	m_vec[1] *= t;
	m_vec[2] *= t;
	return *this;
}

vec3 operator * (const vec3& v1, const vec3& v2)
{
	return vec3(v1.m_vec[0] * v2.m_vec[0], 
		v1.m_vec[1] * v2.m_vec[1], 
		v1.m_vec[2] * v2.m_vec[2]);
}

vec3 operator*(float t, const vec3& v)
{
	return vec3(v.m_vec[0] * t, v.m_vec[1] * t, v.m_vec[2] * t);
}

vec3 operator*(const vec3& v, float t)
{
	return vec3(v.m_vec[0] * t, v.m_vec[1] * t, v.m_vec[2] * t);
}

vec3& vec3::operator *= (const vec3& v2)
{
	m_vec[0] *= v2.m_vec[0];
	m_vec[1] *= v2.m_vec[1];
	m_vec[2] *= v2.m_vec[2];
	return *this;
}

vec3 Normalize(vec3 v)
{
	return v / v.Length();
}


float dot(const vec3& v1, const vec3& v2)
{
	return v1.m_vec[0] * v2.m_vec[0] + 
		v1.m_vec[1] * v2.m_vec[1] + 
		v1.m_vec[2] * v2.m_vec[2];
}

vec3 cross(const vec3& v1, const vec3& v2)
{
	return vec3(v1.m_vec[1] * v2.m_vec[2] - v2.m_vec[1] * v1.m_vec[2], 
		v1.m_vec[2] * v2.m_vec[0] - v2.m_vec[2] * v1.m_vec[0],
		v1.m_vec[0] * v2.m_vec[1] - v2.m_vec[0] * v1.m_vec[1]);
}