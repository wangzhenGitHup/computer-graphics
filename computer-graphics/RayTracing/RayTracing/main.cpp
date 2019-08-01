#include <iostream>
#include "Sphere.h"
#include "HitableList.h"
#include "Camera.h"
#include "Material.h"
#include "vec3.h"
#include "Ray.h"
#include "Hitable.h"
#include "drand48.h"
#include <float.h>

vec3 Color(const Ray& ray, Hitable* world, int depth)
{
	HitRecord rec;
	if (world->hit(ray, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.mat_prt->scatter(ray, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		return vec3(0, 0, 0);
	}
	else
	{
		vec3 unit_direction = Normalize(ray.Direction());
		float t = 0.5 * (unit_direction.Y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

Hitable* random_scene()
{
	int n = 500;
	Hitable** pList = new Hitable*[n + 1];
	pList[0] = new Sphere(vec3(0, -1000, 0), 
		1000, 
		new Lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = drand48();
			vec3 center(a + 0.9 * drand48(), 0.2, b + 0.9 * drand48());
			if ((center - vec3(4, 0.2, 0)).Length() > 0.9)
			{
				if (choose_mat < 0.8) //diffuse
				{
					pList[i++] = new Sphere(center, 0.2, 
						new Lambertian(vec3(drand48() * drand48(), 
						drand48() * drand48(), 
						drand48() * drand48())));
				}
				else if (choose_mat < 0.95) //metal
				{
					pList[i++] = new Sphere(center, 0.2,
						new Metal(
						vec3(
						0.5*(1 + drand48()),
						0.5*(1 + drand48()),
						0.5*(1 + drand48())
						),
						0.5*drand48()
						));
				}
				else //glass
				{
					pList[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	pList[i++] = new Sphere(vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	pList[i++] = new Sphere(vec3(-4, 1, 0), 1.0, new Lambertian(vec3(0.4, 0.2, 0.1)));
	pList[i++] = new Sphere(vec3(4, 1, 0), 1.0, new Metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new HitableList(pList, i);
}


int main()
{
	int nx = 1200;
	int ny = 800;
	int ns = 10;

	std::cout << "P3\n" << nx << "  " << ny << "\n255\n";

	Hitable* pList[5];
	float R = cos(M_PI / 4);

	pList[0] = new Sphere(vec3(0, 0, -1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5)));
	pList[1] = new Sphere(vec3(0, -100.5, -1), 100, new Lambertian(vec3(0.8, 0.8, 0.0)));
	pList[2] = new Sphere(vec3(1, 0, -1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.0));
	pList[3] = new Sphere(vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
	pList[4] = new Sphere(vec3(-1, 0, -1), -0.45, new Dielectric(1.5));

	Hitable*pWorld = new HitableList(pList, 5);
	pWorld = random_scene();

	vec3 lookFrom(13, 2, 3);
	vec3 lookAt(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	Camera camera(lookFrom, lookAt, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48() / float(nx));
				float v = float(j + drand48() / float(ny));
				Ray ray = camera.getRay(u, v);
				vec3 pos = ray.point_at_parameter(2.0);
				col += Color(ray, pWorld, 0);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			std::cout << ir << "  " << ig << "  " << ib << "\n";
		}
	}

	return 0;
}