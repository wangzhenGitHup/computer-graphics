#ifndef __HITABLE__H__
#define __HITABLE__H__

#include "Ray.h"

class Material;

struct HitRecord
{
	float t;
	vec3 p;
	vec3 normal;
	Material* mat_prt;
};

class Hitable
{
public:
	virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const = 0;
};

#endif