#ifndef __MATERIAL__H__
#define __MATERIAL__H__


#include "Ray.h"
#include "Hitable.h"
#include "drand48.h"
#include "vec3.h"

struct HitRecord;

float Schlick(float cosine, float ref_idx);
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);
vec3 reflect(const vec3& v, const vec3& n);
vec3 random_in_unit_sphere();

class Material
{
public:
	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const vec3& value) : m_albedo(value){}
	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray(rec.p, target - rec.p);
		attenuation = m_albedo;
		return true;
	}


public:
	vec3 m_albedo;
};


class Metal : public Material
{
public:
	Metal(const vec3& value, float f) : m_albedo(value)
	{
		if (f < 1)
		{
			m_fuzz = f;
		}
		else
		{
			m_fuzz = 1;
		}
	}

	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 reflected = reflect(Normalize(ray_in.Direction()), rec.normal);
		scattered = Ray(rec.p, reflected + m_fuzz * random_in_unit_sphere());
		attenuation = m_albedo;
		return (dot(scattered.Direction(), rec.normal) > 0);
	}

public:
	vec3 m_albedo;
	float m_fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(float ri) : m_ref_idx(ri){}
	virtual bool scatter(const Ray& ray_in, const HitRecord& rec, vec3& attenuation, Ray& scattered)const
	{
		vec3 outward_normal;
		vec3 reflected = reflect(ray_in.Direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;

		if (dot(ray_in.Direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = m_ref_idx;
			cosine = dot(ray_in.Direction(), rec.normal) / ray_in.Direction().Length();
			cosine = sqrt(1 - m_ref_idx * m_ref_idx * (1 - cosine * cosine));
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / m_ref_idx;
			cosine = -dot(ray_in.Direction(), rec.normal) / ray_in.Direction().Length();
		}

		if (refract(ray_in.Direction(), outward_normal, ni_over_nt, reflected))
		{
			reflect_prob = Schlick(cosine, m_ref_idx);
		}
		else
		{
			reflect_prob = 1.0;
		}

		if (drand48() < reflect_prob)
		{
			scattered = Ray(rec.p, reflected);
		}
		else
		{
			scattered = Ray(rec.p, refracted);
		}

		return true;
	}

public:
	float m_ref_idx;
};
#endif