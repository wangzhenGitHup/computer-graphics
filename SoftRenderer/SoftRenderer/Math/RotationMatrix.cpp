#include "RotationMatrix.h"
#include "SelfVector3D.h"
#include "Quaternions.h"

void RotationMatrix::Identity()
{
	m11 = m22 = m33 = 1.0f;
	m12 = m13 = m21 = m23 = m31 = m32 = 0.0f;
}

void RotationMatrix::setup(const EulerAngles& orientation)
{
	//计算角度的sin和cos值

	float sh, ch, sp, cp, sb, cb;
}

void RotationMatrix::fromInertialToObjectQuaternion(const Quaternions& q)
{
	//m11 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
}

void RotationMatrix::fromObjectToInertialQuaternion(const Quaternions& q)
{

}

_Vector3D RotationMatrix::inertialToObject(const _Vector3D& vec3) const
{
	_Vector3D tmp;
	return tmp;
}

_Vector3D RotationMatrix::objectToInertial(const _Vector3D& vec3) const
{
	_Vector3D tmp;
	return tmp;
}
