#include "Quaternions.h"
#include "SelfVector3D.h"
#include "EulerAngles.h"
#include "SelfMaths.h"

const Quaternions kQuaternionIdentity = { 1.0f, 0.0f, 0.0f, 0.0f };

void Quaternions::setToRotateAboutX(float theta)
{
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternions::setToRotateAboutY(float theta)
{
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

void Quaternions::setToRotateAboutZ(float theta)
{
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

void Quaternions::setToRotateAboutAxis(const _Vector3D& axis, float theta)
{
	if (FLT_EQUAL(axis.GetX(), 1.0f) || FLT_EQUAL(axis.GetY(), 1.0f) || FLT_EQUAL(axis.GetZ(), 1.0f))
	{
		float thetaOver2 = theta * 0.5f;
		float sinThetaOver2 = sin(thetaOver2);

		w = cos(thetaOver2);
		x = axis.GetX() * sinThetaOver2;
		y = axis.GetY() * sinThetaOver2;
		z = axis.GetZ() * sinThetaOver2;
	}
}

void Quaternions::setToRotateObjectToInertial(const EulerAngles& orientation)
{
	
}

void Quaternions::setToRotateInertialToObject(const EulerAngles& orientation)
{

}

Quaternions Quaternions::operator*(const Quaternions& q) const
{
	Quaternions result;
	result.w = w * q.w - x * q.x - y * q.y - z * q.z;
	result.x = w * q.x + x * q.w + z * q.y - y * q.z;
	result.y = w * q.y + y * q.w + x * q.z - z * q.x;
	result.z = w * q.z + z * q.w + y * q.x - x * q.y;

	return result;
}

Quaternions& Quaternions::operator*=(const Quaternions& q)
{
	*this = *this * q;
	return *this;
}

void Quaternions::Normalized()
{
	float len = (float)sqrt(w * w + x * x + y * y + z * z);

	if (len > 0.0f)
	{
		float oneOverMag = 1.0f / len;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else
	{
		Identity();
	}
}

float Quaternions::getRotationAngle() const
{
	//float thetaOver2 = 

	return 0.0f;
}

_Vector3D Quaternions::getRotationAxis() const
{
	float sinThetaOver2Sq = 1.0f - w * w;
	if (sinThetaOver2Sq <= 0.0f)
	{
		return _Vector3D(1.0f, 0.0f, 0.0f);
	}

	float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);
	return _Vector3D(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}


float Dot(const Quaternions& q1, const Quaternions& q2)
{

	return 0.0f;
}

Quaternions slerp(const Quaternions& q1, const Quaternions& q2, float factor)
{
	Quaternions result;

	return result;
}

Quaternions conjugate(const Quaternions& q)
{
	Quaternions result;

	return result;
}

Quaternions Pow(const Quaternions& q, float exponent)
{
	Quaternions result;

	return result;
}