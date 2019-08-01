#ifndef __SPHERE__H__
#define __SPHERE__H__

#include "Hitable.h"

class Sphere : public Hitable
{
public:
	Sphere(){}
	Sphere(vec3 cen, float r, Material* mat) : m_center(cen), m_radius(r), m_material_ptr(mat){}
	virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& rec)const;

public:
	vec3 m_center;
	float m_radius;
	Material* m_material_ptr;
};


#endif