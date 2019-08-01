#include "Ray.h"


Ray::Ray(const vec3& a, const vec3& b)
{
	m_A = a; m_B = b;
}

vec3 Ray::Origin() const
{
	return m_A;
}

vec3 Ray::Direction() const
{
	return m_B;
}

vec3 Ray::point_at_parameter(float t) const
{
	return m_A + t * m_B;
}
