#include "Utils.h"

Matrix4x4 lookAt(float eyeX, float eyeY, float eyeZ, 
	float centerX, float centerY, float centerZ, 
	float upX, float upY, float upZ)
{
	_Vector3D eye;
	eye.Set(eyeX, eyeY, eyeZ);

	_Vector3D center;
	center.Set(centerX, centerY, centerZ);

	_Vector3D up;
	up.Set(upX, upY, upZ);

	_Vector3D viewDir = center - eye;
	viewDir.Normalized();

	_Vector3D n = viewDir;

	_Vector3D u = up.Cross(n);
	u.Normalized();

	_Vector3D v = n.Cross(u);
	v.Normalized();

	//  |ux  uy  uz  0|     |1  0  0  -eyeX|
	//  |vx  vy  vz  0|  *  |0  1  0  -eyeY|
	//  |nx  ny  nz  0|     |0  0  1  -eyeZ|
	//  |0   0   0   1|     |0  0  0     1 |
	//×ªÖÃÏÂ

	Matrix4x4 mat;
	mat.LoadIdentity();
	mat.SetElement(0, u.GetX());
	mat.SetElement(1, v.GetX());
	mat.SetElement(2, n.GetX());

	mat.SetElement(4, u.GetY());
	mat.SetElement(5, v.GetY());
	mat.SetElement(6, n.GetY());

	mat.SetElement(8, u.GetZ());
	mat.SetElement(9, v.GetZ());
	mat.SetElement(10, n.GetZ());
	mat.SetElement(12, -u.Dot(eye));
	mat.SetElement(13, -v.Dot(eye));
	mat.SetElement(14, -n.Dot(eye));
	return mat;
}

Matrix4x4 perspective(float fovy, float aspect, float zNear, float zFar)
{
	Matrix4x4 mat;
	mat.SetPerspective(fovy, aspect, zNear, zFar);
	return mat;
}

Matrix4x4 ortho(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4x4 mat;
	mat.SetOrtho(left, right, bottom, top, near, far);
	return mat;
}

Matrix4x4 rotateX(float angle)
{
	Matrix4x4 mat;
	mat.SetRotationX(angle);
	return mat;
}

Matrix4x4 rotateY(float angle)
{
	Matrix4x4 mat;
	mat.SetRotationY(angle);
	return mat;
}

Matrix4x4 rotateZ(float angle)
{
	Matrix4x4 mat;
	mat.SetRotationZ(angle);
	return mat;
}

Matrix4x4 scale(float size)
{
	Matrix4x4 mat;
	mat.LoadIdentity();
	mat.SetElement(0, size);
	mat.SetElement(5, size);
	mat.SetElement(10, size);
	return mat;
}

Matrix4x4 translate(float tx, float ty, float tz)
{
	Matrix4x4 mat;
	mat.SetTranslation(_Vector3D(tx, ty, tz));
	return mat;
}

_Vector4D mul(_Vector4D a, _Vector4D b)
{
	_Vector4D result;
	result.SetX(a.GetX() * b.GetX());
	result.SetY(a.GetY() * b.GetY());
	result.SetZ(a.GetZ() * b.GetZ());
	result.SetW(a.GetW() * b.GetW());
	return result;
}

void interpolate3f(float pa, float pb, float pc, 
	float a, float b, float c, 
	float& result)
{
	result = pa * a + pb * b + pc * c;
}

void interpolate2f(float pa, float pb, 
	float a, float b, 
	float& result)
{
	result = pa * a + pb * b;
}

float calZPara(float v1z, float v2z, float z)
{
	return (z - v2z) / (v1z - v2z);
}

_Vector3D calcParaVec(_Vector3D vec1, _Vector3D vec2, float param)
{
	_Vector3D result;
	result = param * (vec1 - vec2) + vec2;
	return result;
}

float Roundf(float number)
{
	return number < 0.0f ? ceilf(number - 0.5f) : floorf(number + 0.5f);
}
