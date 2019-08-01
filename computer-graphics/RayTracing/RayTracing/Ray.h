#ifndef __RAY__H__
#define __RAY__H__

#include "vec3.h"

class Ray
{
public:
	Ray(){}
	Ray(const vec3& a, const vec3& b);
	vec3 Origin() const;
	vec3 Direction() const;
	//参数直线方程
	vec3 point_at_parameter(float t)const;

public:
	vec3 m_A;
	vec3 m_B;
};

#endif