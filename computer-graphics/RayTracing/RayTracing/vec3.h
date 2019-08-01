#ifndef __VEC3__H__
#define __VEC3__H__

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:
	vec3(){}
	vec3(float e0, float e1, float e2)
	{
		m_vec[0] = e0;
		m_vec[1] = e1;
		m_vec[2] = e2;
	}

	inline float X() const{ return m_vec[0]; }
	inline float Y() const{ return m_vec[1]; }
	inline float Z() const{ return m_vec[2]; }
	inline float R() const{ return m_vec[0]; }
	inline float G() const{ return m_vec[1]; }
	inline float B() const{ return m_vec[2]; }

	inline const vec3& operator + () const{ return *this; }
	inline vec3 operator - () const{ return vec3(-m_vec[0], -m_vec[1], -m_vec[2]); }
	inline float operator [] (int i) const { return m_vec[i]; }
	inline float& operator [] (int i) { return m_vec[i]; }

	inline vec3& operator += (const vec3& v2)
	{
		m_vec[0] += v2.m_vec[0];
		m_vec[1] += v2.m_vec[1];
		m_vec[2] += v2.m_vec[2];
		return *this;
	}

	inline vec3& operator -= (const vec3& v2);
	inline vec3& operator *= (const vec3& v2);
	inline vec3& operator /= (const vec3& v2)
	{
		m_vec[0] /= v2.m_vec[0];
		m_vec[1] /= v2.m_vec[1];
		m_vec[2] /= v2.m_vec[2];
		return *this;
	}

	inline vec3& operator *= (const float t);
	inline vec3& operator /= (const float t)
	{
		m_vec[0] /= t;
		m_vec[1] /= t;
		m_vec[2] /= t;
		return *this;
	}

	inline float Length()const{ return sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]); }
	inline float squared_length()const{ return m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]; }
	inline void Normalize();


	float m_vec[3];
};


vec3 Normalize(vec3 v);

std::istream& operator >> (std::istream& is, vec3& t);
std::ostream& operator << (std::ostream& os, const vec3& t);
vec3 operator + (const vec3& v1, const vec3& v2);
vec3 operator - (const vec3& v1, const vec3& v2);
vec3 operator * (const vec3& v1, const vec3& v2);
vec3 operator / (const vec3& v1, const vec3& v2);
vec3 operator * (const vec3& v, float t);
vec3 operator * (float t, const vec3& v);
vec3 operator / (const vec3& v, float t);
float dot(const vec3& v1, const vec3& v2);
vec3 cross(const vec3& v1, const vec3& v2);

#endif