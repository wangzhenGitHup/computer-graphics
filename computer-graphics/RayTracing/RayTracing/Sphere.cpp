#include "Sphere.h"
#include "vec3.h"
#include "Ray.h"
#include "Material.h"

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitRecord& rec) const
{
	vec3 oc = ray.Origin() - m_center;
	float a = dot(ray.Direction(), ray.Direction());
	float b = dot(oc, ray.Direction());
	float c = dot(oc, oc) - m_radius * m_radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - m_center) / m_radius;
			rec.mat_prt = m_material_ptr;
			return true;
		}
	}

	return false;
}
