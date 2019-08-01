#ifndef __CAMERA__H__
#define __CAMERA__H__


#include "Ray.h"
#include "drand48.h"
#include "vec3.h"

#define M_PI       3.14159265358979323846

vec3 random_in_unit_disk()
{
	vec3 pos;

	do 
	{
		pos = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
	} while (dot(pos, pos) >= 1.0);

	return pos;
}


class Camera
{
public:
	Camera(vec3 lookFrom, vec3 lookAt, vec3 vUp, float vFov, float aspect, float aperture, float focus_dist)
	{
		m_lens_radius = aperture / 2;
		float theta = vFov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		m_origin = lookFrom;

		w = Normalize(lookFrom - lookAt);
		u = Normalize(cross(vUp, w));
		v = cross(w, u);

		m_lower_left_corner = m_origin -
			half_width * focus_dist * u -
			half_height * focus_dist * v -
			focus_dist * w;
		m_horizontal = 2 * half_width * focus_dist * u;
		m_vertical = 2 * half_height * focus_dist * v;
	}


	Ray getRay(float s, float t)
	{
		vec3 rd = m_lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.X() + v * rd.Y();
		return Ray(m_origin + offset,
			m_lower_left_corner +
			s * m_horizontal +
			t * m_vertical - m_origin - offset);
	}

public:
	vec3 m_origin;
	vec3 m_lower_left_corner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 u, v, w;
	float m_lens_radius;
};

#endif // !__CAMERA__H__
