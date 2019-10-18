#include "Plane.h"
#include "SelfMaths.h"

Plane::Plane()
{
	_normal = _Vector3D(0.0f, 0.0f, 0.0f);
}

Plane::Plane(const Plane& plane)
{
	_normal = plane._normal;
}

void Plane::SetNormal(const _Vector3D& vec)
{
	_normal = vec;
}

void Plane::SetFromPoints(const _Vector3D& p0, const _Vector3D& p1, const _Vector3D& p2)
{
	//计算平面法线
	_Vector3D tmpVec = p1 - p0;
	_normal = tmpVec.Cross(p2 - p0);
	//归一化
	_normal.Normalized();
}


void Plane::Normalized()
{
	float len = _normal.GetLength();
	if (FLT_IS_ZERO(len))
	{
		return;
	}
	_normal /= len;
}

float Plane::GetDistance(const _Vector3D& vec) const
{
	//向量到平面的距离就是某向量在平面法线上的投影
	// 向量p1在平面法线n上的投影为: p1.n =  p1.x * n.x + p1.y * n.y + p1.z * n.z;
	return vec.GetX() * _normal.GetX() + vec.GetY() * _normal.GetY() + vec.GetZ() * _normal.GetZ();
}

int Plane::ClassifyPoint(const _Vector3D& vec) const
{
	float distance = GetDistance(vec);
	if (distance > FLT_EPSILON)
	{
		return POINT_IN_FRONT_OF_PLANE;
	}

	if (distance < -FLT_EPSILON)
	{
		return POINT_BEHIND_PLANE;
	}

	return POINT_ON_PLANE;
}

Plane Plane::Lerp(const Plane& plane, float factor)
{
	Plane result;
	_Vector3D tmpNormal = _normal * (1.0f - factor) + plane.GetNormal() * factor;
	result.SetNormal(tmpNormal);
	result.GetNormal().Normalized();
	return result;
}

Plane Plane::operator-() const
{
	return Plane(-_normal);
}

Plane Plane::operator+() const
{
	return (*this);
}

bool Plane::operator!=(const Plane& plane) const
{
	return !((*this) == plane);
}

bool Plane::operator==(const Plane& plane) const
{
	if (_normal == plane.GetNormal())
	{
		return true;
	}

	return false;
}
