#ifndef __HITABLE__LIST__H__
#define __HITABLE__LIST__H__

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList(){}
	HitableList(Hitable** list, int n){ m_list = list; m_list_size = n; }
	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec)const;

public:
	Hitable** m_list;
	int m_list_size;
};

#endif