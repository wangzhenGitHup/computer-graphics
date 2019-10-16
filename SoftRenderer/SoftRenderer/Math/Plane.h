#ifndef  __PLANE__H__
#define  __PLANE__H__

#include "SelfVector3D.h"

class Plane
{
public:
	Plane();
	Plane(_Vector3D normal) : _normal(normal){}
	Plane(const Plane& plane);
	~Plane(){}

	void SetNormal(const _Vector3D& vec);
	void SetFromPoints(const _Vector3D& p0, const _Vector3D& p1, const _Vector3D& p2);
	void Normalized();
	_Vector3D GetNormal()const{ return _normal; }
	float GetDistance(const _Vector3D& vec)const;
	int ClassifyPoint(const _Vector3D& vec)const;
	Plane Lerp(const Plane& plane, float factor);

	//±È½Ï
	bool operator==(const Plane& plane)const;
	bool operator!=(const Plane& plane)const;

	//Õý¸º
	Plane operator-()const;
	Plane operator+()const;

private:
	_Vector3D _normal;

	const int POINT_ON_PLANE = 0;
	const int POINT_IN_FRONT_OF_PLANE = 1;
	const int POINT_BEHIND_PLANE = 2;
};
#endif