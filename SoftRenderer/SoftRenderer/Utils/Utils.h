#ifndef  __UTILS__H__
#define  __UTILS__H__

#include "SelfVector3D.h"
#include "SelfVector4D.h"
#include "SelfMatrix4x4.h"
#include "SelfMaths.h"

//�ӵ�
Matrix4x4 lookAt(float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ);
//ͶӰ����
Matrix4x4 perspective(float fovy, float aspect, float zNear, float zFar);
//��������
Matrix4x4 ortho(float left, float right, float bottom, float top, float near, float far);

Matrix4x4 rotateX(float angle);
Matrix4x4 rotateY(float angle);
Matrix4x4 rotateZ(float angle);
Matrix4x4 scale(float size);
Matrix4x4 translate(float tx, float ty, float tz);
_Vector4D mul(_Vector4D a, _Vector4D b);

//��ֵ����
void interpolate3f(float pa, float pb, float pc,
	float a, float b, float c, float& result);
void interpolate2f(float pa, float pb, float a, float b, float& result);

float calZPara(float v1z, float v2z, float z);
//�������������㹫ʽ
_Vector3D calcParaVec(_Vector3D vec1, _Vector3D vec2, float param);

float Roundf(float number);


#endif