#include "HitableList.h"

bool HitableList::hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const
{
	HitRecord tmp_rec;
	bool bHitAnything = false;
	double closestSoFar = tMax;

	for (int i = 0; i < m_list_size; i++)
	{
		if (m_list[i]->hit(ray, tMin, closestSoFar, tmp_rec))
		{
			bHitAnything = true;
			closestSoFar = tmp_rec.t;
			rec = tmp_rec;
		}
	}

	return bHitAnything;
}
