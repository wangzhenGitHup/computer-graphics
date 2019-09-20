#include "SelfMatrix4x4.h"
#include "SelfVector4D.h"
#include "SelfVector3D.h"
#include "SelfMaths.h"
#include <memory.h>

Matrix4x4::Matrix4x4()
{
	LoadIdentity();
}

Matrix4x4::Matrix4x4(float m0, float m1, float m2, float m3, 
	float m4, float m5, float m6, float m7, 
	float m8, float m9, float m10, float m11, 
	float m12, float m13, float m14, float m15)
{
	_elements[0] = m0;
	_elements[1] = m1;
	_elements[2] = m2;
	_elements[3] = m3;
	_elements[4] = m4;
	_elements[5] = m5;
	_elements[6] = m6;
	_elements[7] = m7;
	_elements[8] = m8;
	_elements[9] = m9;
	_elements[10] = m10;
	_elements[11] = m11;
	_elements[12] = m12;
	_elements[13] = m13;
	_elements[14] = m14;
	_elements[15] = m15;
}

Matrix4x4::Matrix4x4(const float* v)
{
	memcpy(_elements, v, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix)
{
	memcpy(_elements, matrix._elements, 16 * sizeof(float));
}

void Matrix4x4::LoadIdentity()
{
	memset(_elements, 0, 16 * sizeof(float));
	_elements[0] = 1.0f;
	_elements[5] = 1.0f;
	_elements[10] = 1.0f;
	_elements[15] = 1.0f;
}

void Matrix4x4::SetElement(int pos, float v)
{
	if (pos >= 0 && pos <= 15)
	{
		_elements[pos] = v;
	}
}

float Matrix4x4::GetElement(int pos) const
{
	if (pos >= 0 && pos <= 15)
	{
		return _elements[pos];
	}

	return 0.0f;
}

_Vector4D Matrix4x4::GetColumn(int pos) const
{
	switch (pos)
	{
	case 0:
		return _Vector4D(_elements[0], _elements[4], _elements[8], _elements[12]);

	case 1:
		return _Vector4D(_elements[1], _elements[5], _elements[9], _elements[13]);

	case 2:
		return _Vector4D(_elements[2], _elements[6], _elements[10], _elements[14]);

	case 3:
		return _Vector4D(_elements[3], _elements[7], _elements[11], _elements[15]);

	default:
		return _Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

_Vector4D Matrix4x4::GetRow(int pos) const
{
	switch (pos)
	{
	case 0:
		return _Vector4D(_elements[0], _elements[1], _elements[2], _elements[3]);

	case 1:
		return _Vector4D(_elements[4], _elements[5], _elements[6], _elements[7]);

	case 2:
		return _Vector4D(_elements[8], _elements[9], _elements[10], _elements[11]);

	case 3:
		return _Vector4D(_elements[12], _elements[13], _elements[14], _elements[15]);

	default:
		return _Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void Matrix4x4::LoadZero()
{
	memset(_elements, 0, 16 * sizeof(float));
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& matrix) const
{
	return Matrix4x4(_elements[0] + matrix._elements[0],
		_elements[1] + matrix._elements[1], 
		_elements[2] + matrix._elements[2], 
		_elements[3] + matrix._elements[3], 
		_elements[4] + matrix._elements[4], 
		_elements[5] + matrix._elements[5], 
		_elements[6] + matrix._elements[6], 
		_elements[7] + matrix._elements[7], 
		_elements[8] + matrix._elements[8], 
		_elements[9] + matrix._elements[9], 
		_elements[10] + matrix._elements[10], 
		_elements[11] + matrix._elements[11], 
		_elements[12] + matrix._elements[12], 
		_elements[13] + matrix._elements[13], 
		_elements[14] + matrix._elements[14], 
		_elements[15] + matrix._elements[15] );
}

Matrix4x4 Matrix4x4::operator+() const
{
	return (*this);
}

void Matrix4x4::RotateVector3D(_Vector3D& v3) const
{
	v3 = GetRotatedVector3D(v3);
}

void Matrix4x4::InverseRotateVector3D(_Vector3D& v3) const
{
	v3 = GetInverseRotatedVector3D(v3);
}

_Vector3D Matrix4x4::GetRotatedVector3D(const _Vector3D& v3) const
{
	return _Vector3D(
		_elements[0] * v3.GetX() + _elements[4] * v3.GetY() + _elements[8] * v3.GetZ(),
		_elements[1] * v3.GetX() + _elements[5] * v3.GetY() + _elements[9] * v3.GetZ(), 
		_elements[2] * v3.GetX() + _elements[6] * v3.GetY() + _elements[10] * v3.GetZ()
		);
}

_Vector3D Matrix4x4::GetInverseRotatedVector3D(const _Vector3D& v3) const
{
	return _Vector3D(
		_elements[0] * v3.GetX() + _elements[1] * v3.GetY() + _elements[2] * v3.GetZ(),
		_elements[4] * v3.GetX() + _elements[5] * v3.GetY() + _elements[6] * v3.GetZ(),
		_elements[8] * v3.GetX() + _elements[9] * v3.GetY() + _elements[10] * v3.GetZ()
		);
}

void Matrix4x4::TranslateVector3D(_Vector3D& v3) const
{
	v3 = GetTranslatedVector3D(v3);
}

void Matrix4x4::InverseTranslateVector3D(_Vector3D& v3) const
{
	v3 = GetInverseTranslatedVector3D(v3);
}

_Vector3D Matrix4x4::GetTranslatedVector3D(const _Vector3D& v3) const
{
	return _Vector3D(
		v3.GetX() + _elements[12], 
		v3.GetY() + _elements[13], 
		v3.GetZ() + _elements[14]
		);
}

_Vector3D Matrix4x4::GetInverseTranslatedVector3D(const _Vector3D& v3) const
{
	//平移变化的逆矩阵直接减去元素值
	return _Vector3D(
		v3.GetX() - _elements[12],
		v3.GetY() - _elements[13],
		v3.GetZ() - _elements[14]
		);
}

void Matrix4x4::Inverse()
{
	*this = GetInverse();
}

Matrix4x4 Matrix4x4::GetInverse() const
{
	Matrix4x4 result = GetInverseTranspose();
	result.Transpose();
	return result;
}

void Matrix4x4::Transpose()
{
	*this = GetTranspose();
}

Matrix4x4 Matrix4x4::GetTranspose() const
{
	//行列置换
	return Matrix4x4(
		_elements[0], _elements[4], _elements[8], _elements[12],
		_elements[1], _elements[5], _elements[9], _elements[13],
		_elements[2], _elements[6], _elements[10], _elements[14],
		_elements[3], _elements[7], _elements[11], _elements[15]
		);
}

void Matrix4x4::InverseTranspose()
{
	*this = GetInverseTranspose();
}

Matrix4x4 Matrix4x4::GetInverseTranspose()const
{
	//利用公式 矩阵A的逆 = 矩阵A的伴随矩阵 / 矩阵A行列式的值
	//伴随矩阵
	Matrix4x4 followMat;
	Matrix4x4 result;
	float tmp[12];
	//行列式的值
	float determinant;

	//以下这些就是根据线代伴随矩阵的计算公式进行求导
	tmp[0] = _elements[10] * _elements[15];
	tmp[1] = _elements[11] * _elements[14];
	tmp[2] = _elements[9] * _elements[15];
	tmp[3] = _elements[11] * _elements[13];
	tmp[4] = _elements[9] * _elements[14];
	tmp[5] = _elements[10] * _elements[13];
	tmp[6] = _elements[8] * _elements[15];
	tmp[7] = _elements[11] * _elements[12];
	tmp[8] = _elements[8] * _elements[14];
	tmp[9] = _elements[10] * _elements[12];
	tmp[10] = _elements[8] * _elements[13];
	tmp[11] = _elements[9] * _elements[12];

	//第1行第1列的代数余子式值
	followMat.SetElement(0,
		tmp[0] * _elements[5] + 
		tmp[3] * _elements[6] + 
		tmp[4] * _elements[7] - 
		tmp[1] * _elements[5] - 
		tmp[2] * _elements[6] - 
		tmp[5] * _elements[7]);

	//第1行第2列的代数余子式值
	followMat.SetElement(1,
		tmp[1] * _elements[4] + 
		tmp[6] * _elements[6] + 
		tmp[9] * _elements[7] - 
		tmp[0] * _elements[4] - 
		tmp[7] * _elements[6] - 
		tmp[8] * _elements[7]);

	//第1行第3列的代数余子式值
	followMat.SetElement(2,
		tmp[2] * _elements[4] + 
		tmp[7] * _elements[5] + 
		tmp[10] * _elements[7] - 
		tmp[3] * _elements[4] - 
		tmp[6] * _elements[5] - 
		tmp[11] * _elements[7]);

	//第1行第4列的代数余子式值
	followMat.SetElement(3,
		tmp[5] * _elements[4] +
		tmp[8] * _elements[5] +
		tmp[11] * _elements[6] -
		tmp[4] * _elements[4] -
		tmp[9] * _elements[5] -
		tmp[10] * _elements[6]);

	//第2行第1列的代数余子式值
	followMat.SetElement(4,
		tmp[1] * _elements[1] +
		tmp[2] * _elements[2] +
		tmp[5] * _elements[3] -
		tmp[0] * _elements[1] -
		tmp[3] * _elements[2] -
		tmp[4] * _elements[3]);

	//第2行第2列的代数余子式值
	followMat.SetElement(5,
		tmp[0] * _elements[0] +
		tmp[7] * _elements[2] +
		tmp[8] * _elements[3] -
		tmp[1] * _elements[0] -
		tmp[6] * _elements[2] -
		tmp[9] * _elements[3]);

	//第2行第3列的代数余子式值
	followMat.SetElement(6,
		tmp[3] * _elements[0] +
		tmp[6] * _elements[1] +
		tmp[11] * _elements[3] -
		tmp[2] * _elements[0] -
		tmp[7] * _elements[1] -
		tmp[10] * _elements[3]);

	//第2行第4列的代数余子式值
	followMat.SetElement(7,
		tmp[4] * _elements[0] +
		tmp[9] * _elements[1] +
		tmp[10] * _elements[2] -
		tmp[5] * _elements[0] -
		tmp[8] * _elements[1] -
		tmp[11] * _elements[2]);

	tmp[0] = _elements[2] * _elements[7];
	tmp[1] = _elements[3] * _elements[6];
	tmp[2] = _elements[1] * _elements[7];
	tmp[3] = _elements[3] * _elements[5];
	tmp[4] = _elements[1] * _elements[6];
	tmp[5] = _elements[2] * _elements[5];
	tmp[6] = _elements[0] * _elements[7];
	tmp[7] = _elements[3] * _elements[4];
	tmp[8] = _elements[0] * _elements[6];
	tmp[9] = _elements[2] * _elements[4];
	tmp[10] = _elements[0] * _elements[5];
	tmp[11] = _elements[1] * _elements[4];

	//第3行第1列的代数余子式值
	followMat.SetElement(8,
		tmp[0] * _elements[13] +
		tmp[3] * _elements[14] +
		tmp[4] * _elements[15] -
		tmp[1] * _elements[13] -
		tmp[2] * _elements[14] -
		tmp[5] * _elements[15]);

	//第3行第2列的代数余子式值
	followMat.SetElement(9,
		tmp[1] * _elements[12] +
		tmp[6] * _elements[14] +
		tmp[9] * _elements[15] -
		tmp[0] * _elements[12] -
		tmp[7] * _elements[14] -
		tmp[8] * _elements[15]);

	//第3行第3列的代数余子式值
	followMat.SetElement(10,
		tmp[2] * _elements[12] +
		tmp[7] * _elements[13] +
		tmp[10] * _elements[15] -
		tmp[3] * _elements[12] -
		tmp[6] * _elements[13] -
		tmp[11] * _elements[15]);

	//第3行第4列的代数余子式值
	followMat.SetElement(11,
		tmp[5] * _elements[12] +
		tmp[8] * _elements[13] +
		tmp[11] * _elements[14] -
		tmp[4] * _elements[12] -
		tmp[9] * _elements[13] -
		tmp[10] * _elements[14]);

	//第4行第1列的代数余子式值
	followMat.SetElement(12,
		tmp[2] * _elements[10] +
		tmp[5] * _elements[11] +
		tmp[1] * _elements[9] -
		tmp[4] * _elements[11] -
		tmp[0] * _elements[9] -
		tmp[3] * _elements[10]);

	//第4行第2列的代数余子式值
	followMat.SetElement(13,
		tmp[8] * _elements[11] +
		tmp[0] * _elements[8] +
		tmp[7] * _elements[10] -
		tmp[6] * _elements[10] -
		tmp[9] * _elements[11] -
		tmp[1] * _elements[8]);

	//第4行第3列的代数余子式值
	followMat.SetElement(14,
		tmp[6] * _elements[9] +
		tmp[11] * _elements[11] +
		tmp[3] * _elements[8] -
		tmp[10] * _elements[11] -
		tmp[2] * _elements[8] -
		tmp[7] * _elements[9]);

	//第4行第4列的代数余子式值
	followMat.SetElement(15,
		tmp[10] * _elements[10] +
		tmp[4] * _elements[8] +
		tmp[9] * _elements[9] -
		tmp[8] * _elements[9] -
		tmp[11] * _elements[10] -
		tmp[5] * _elements[8]);

	//求原矩阵的行列式的值
	//按第一行展开计算
	determinant = _elements[0] * followMat.GetElement(0) +
		_elements[1] * followMat.GetElement(1) +
		_elements[2] * followMat.GetElement(2) +
		_elements[3] * followMat.GetElement(3);

	//矩阵的行列式值不能为0
	if (FLT_IS_ZERO(determinant))
	{
		Matrix4x4 defaultMat;
		return defaultMat;
	}

	//最终得到的逆矩阵[按行排列]
	result = followMat / determinant;
	return result;
}

void Matrix4x4::AffineInverse()
{
	*this = GetAffineInverse();
}

Matrix4x4 Matrix4x4::GetAffineInverse() const
{
	//平移的逆，反向减去
	return Matrix4x4(_elements[0], _elements[4], _elements[8], 0.0f,
		_elements[1], _elements[5], _elements[9], 0.0f,
		_elements[2], _elements[6], _elements[10], 0.0f,
		-(_elements[0] * _elements[12] + _elements[1] * _elements[13] + _elements[2] * _elements[14]),
		-(_elements[4] * _elements[12] + _elements[5] * _elements[13] + _elements[6] * _elements[14]),
		-(_elements[8] * _elements[12] + _elements[9] * _elements[13] + _elements[10] * _elements[14]),
		1.0f);
}

void Matrix4x4::AffineInverseTranspose()
{
	*this = GetAffineInverseTranspose();
}

Matrix4x4 Matrix4x4::GetAffineInverseTranspose()
{
	return Matrix4x4(_elements[0], _elements[1], _elements[2], -(_elements[0] * _elements[12] + _elements[1] * _elements[13] + _elements[2] * _elements[14]),
		_elements[4], _elements[5], _elements[6], -(_elements[4] * _elements[12] + _elements[5] * _elements[13] + _elements[6] * _elements[14]),
		_elements[8], _elements[9], _elements[10], -(_elements[8] * _elements[12] + _elements[9] * _elements[13] + _elements[10] * _elements[14]),
		0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4x4::SetTranslation(const _Vector3D& translation)
{
	LoadIdentity();
	SetTranslationPart(translation);
}

void Matrix4x4::SetScale(const _Vector3D& v3)
{
	LoadIdentity();
	_elements[0] = v3.GetX();
	_elements[5] = v3.GetY();
	_elements[10] = v3.GetZ();
}

void Matrix4x4::SetUniformScale(const float factor)
{
	LoadIdentity();
	_elements[0] = _elements[5] = _elements[10] = factor;
}

void Matrix4x4::SetRotationAxis(const double angle, const _Vector3D& axis)
{
	//这个推导过程 主要是参考《3D数学基础：图形与游戏开发》一书中第8章内容
	//假定 向量V 绕 R轴[Rx, Ry, Rz] 旋转 a角 得到 V'
	//转换成用 矩阵RMatrix*V 来得到 V'
	//为求得 矩阵RMatrix， 我们假定在垂直于 R轴所在平面中解决，转化成方便处理的2D问题
	//为了做到这点， 将 向量V 分解为两个分量：Vv(垂直R轴的向量) 和 Vh(平行于R轴的向量)
	//其中 V = Vv + Vh
	//Vh平行 R轴，所以 V 绕R轴旋转 可转化成求解 Vv绕 R轴旋转 得到Vv'
	//这样 V' = Vv' + Vh     （2）
	//因为 Vh平行 R轴，求Vh等同于求V在R轴上的投影，可得 Vh = (V.R)*R;
	//由 V = Vv + Vh 可得：Vv = V - （V.R)*R;
	//构建一个(Vv,W,R)的正交坐标系，【x代表向量的叉乘】W = R x Vv; Vv = V - Vh；可得：W =  R x [V -Vh]
	//W = R x V - R x Vh = R x V;  (3)
	//因为 Vv'是 Vv 绕 R轴旋转a角得到的,所以 Vv' = Vv*cosa + W*sina;
	//综合（2）(3)可得：Vv' = Vv*cosa + (R x V)*sina
	//又因为 Vv = V - Vh = V - (V.R)*R;
	//所以 Vv' = [V - (V.R)*R]*cosa + (R x V)*sina;
	//可得 V' = Vv' + Vh = [V - (V.R)*R]*cosa + (R x V)*sina + (V.R)*R
	
	//确定第一个基向量[1, 0, 0]代入可得：
	//[Rx * Rx(1 - cosa) + cosa,  Rx * Ry(1 - cosa) + Rz * sina,  Rx * Rz(1 -cosa) - Ry * sina]
	
	//确定第二个基向量[0, 1, 0]代入可得：
	//[Rx * Ry(1 - cosa) - Rz * sina,  Ry * Ry(1 - cosa) + cosa, Ry * Rz(1 - cosa) + Rx * sina]

	//确定第三个基向量[0, 0, 1]代入可得：
	//[Rx * Rz(1 - cosa) + Ry * sina,  Ry * Rz(1 - cosa) - Rz * sina, Rz * Rz(1 - cosa) + cosa]


	//只是旋转，只要确定方向就行了，归一化向量，也可简化计算
	_Vector3D tmpVec = axis.GetNormalized();

	//转成弧度
	float sinAngle = (float)sin(M_PI * angle / 180);
	float cosAngle = (float)cos(M_PI * angle / 180);
	float oneMinusCosAngle = (float)(1.0f - cosAngle);

	LoadIdentity();

	_elements[0] = tmpVec.GetX() * tmpVec.GetX() + cosAngle * (1 - tmpVec.GetX() * tmpVec.GetX());
	_elements[4] = tmpVec.GetX() * tmpVec.GetY() * oneMinusCosAngle - sinAngle * tmpVec.GetZ();
	_elements[8] = tmpVec.GetX() * tmpVec.GetZ() * oneMinusCosAngle + sinAngle * tmpVec.GetY();

	_elements[1] = tmpVec.GetX() * tmpVec.GetY() * oneMinusCosAngle + sinAngle * tmpVec.GetZ();
	_elements[5] = tmpVec.GetY() * tmpVec.GetY() + cosAngle * (1 - tmpVec.GetY() * tmpVec.GetY());
	_elements[9] = tmpVec.GetY() * tmpVec.GetZ() * oneMinusCosAngle - sinAngle * tmpVec.GetX();

	_elements[2] = tmpVec.GetX() * tmpVec.GetZ() * oneMinusCosAngle - sinAngle * tmpVec.GetY();
	_elements[6] = tmpVec.GetY() * tmpVec.GetZ() * oneMinusCosAngle + sinAngle * tmpVec.GetX();
	_elements[10] = tmpVec.GetZ() * tmpVec.GetZ() + cosAngle * (1 - tmpVec.GetZ() * tmpVec.GetZ());
}

void Matrix4x4::SetRotationX(const double angle)
{
	//左手坐标系
	//  ↑ z
	//  |     .p'(y', z')
	//  |    .      .p(y, z)
	//  |   .     .
	//  |  .  b .
	//  | .   .
	//  |.  . 
	//  | .    a
	//  ------------------------>y
	//  y = r*cosa;  z = r*sina;
	//  y' = ax + by + cz;  z' = dx + ey + fz; x' = x;
	//  y'= r*cos(a+b) = r*cosa*cosb - r*sina*sinb = y*cosb - z*sinb;
	//  z'= r*sin(a+b) = r*sina*cosb + r*sinb*cosa = z*cosb + y*sinb;
	//  |x'|   |1     0      0  0|   |x|
	//  |y'| = |0  cosb  -sinb  0| * |y| 
	//  |z'|   |0  sinb   cosb  0|   |z| 
	//  |1 |   |0   0      0    1|   |1|
	//转成行向量
	//                                     |1   0      0    0|
	//  [x'  y'  z'  1] = [x  y  z  1]  *  |0  cosb   sinb  0|
	//                                     |0  -sinb  cosb  0|
	//                                     |0   0      0    1|
	LoadIdentity();
	_elements[5] = (float)cos(M_PI * angle / 180);
	_elements[6] = (float)sin(M_PI * angle / 180);
	_elements[9] = -_elements[6];
	_elements[10] = _elements[5];
}

void Matrix4x4::SetRotationY(const double angle)
{
	//左手坐标系
	//  ↑ x
	//  |     .p'(z', x')
	//  |    .      .p(z, x)
	//  |   .     .
	//  |  .  b .
	//  | .   .
	//  |.  . 
	//  | .    a
	//  ------------------------>z
	//  z = r*cosa;  x = r*sina;
	//  z' = ax + by + cz;  x' = dx + ey + fz; y' = y;
	//  z'= r*cos(a+b) = r*cosa*cosb - r*sina*sinb = z*cosb - x*sinb;
	//  x'= r*sin(a+b) = r*sina*cosb + r*sinb*cosa = x*cosb + z*sinb;
	//  |x'|   |cosb  0   sinb  0|    |x|
	//  |y'| = |0     1      0  0| *  |y|
	//  |z'|   |-sinb 0   cosb  0|    |z|
	//  |1 |   |0     0     0   1|    |1|
	//转成行向量
	//                                     |cosb  0  -sinb  0|
	//  [x'  y'  z'  1] = [x  y  z  1]  *  |0     1    0    0|
	//                                     |sinb  0   cosb  0|
	//                                     |0     0    0    1|
	LoadIdentity();
	_elements[0] = (float)cos(M_PI * angle / 180);
	_elements[2] = -(float)sin(M_PI * angle / 180);
	_elements[8] = -_elements[2];
	_elements[10] = _elements[0];
}

void Matrix4x4::SetRotationZ(const double angle)
{
	//左手坐标系
	//  ↑ y
	//  |     .p'(x', y')
	//  |    .      .p(x, y)
	//  |   .     .
	//  |  .  b .
	//  | .   .
	//  |.  . 
	//  | .    a
	//  ------------------------>x
	//  x = r*cosa;  y = r*sina;
	//  x' = ax + by + cz;  y' = dx + ey + fz; z' = z;
	//  x'= r*cos(a+b) = r*cosa*cosb - r*sina*sinb = x*cosb - y*sinb;
	//  y'= r*sin(a+b) = r*sina*cosb + r*sinb*cosa = y*cosb + x*sinb;
	//  |x'|   |cosb -sinb 0   0|   |x|
	//  |y'| = |sinb cosb  0   0| * |y|
	//  |z'|   |0     0    1   0|   |z|
	//  |1 |   |0     0    0   1|   |1|
	//转成行向量
	//                                     |cosb   sinb  0  0|
	//  [x'  y'  z'  1] = [x  y  z  1]  *  |-sinb  cosb  0  0|
	//                                     |0       0    1  0|
	//                                     |0       0    0  1|
	LoadIdentity();
	_elements[0] = (float)cos(M_PI * angle / 180);
	_elements[1] = (float)sin(M_PI * angle / 180);
	_elements[4] = -_elements[1];
	_elements[5] = _elements[0];
}

void Matrix4x4::SetOrtho(float left, float right, float bottom, float top, float near, float far)
{
	//推导过程： 左手坐标系
	//              ▴ y
	//              │
	//              │     
	//              │     /z
	//              │    /
	//              |   /
	//              |  /
	//              | /
	//              |/
	//               ―――――――――――――――――――▸x

	//从(-1, -1, 0)到(1, 1, 1),原点在立方体前面正中心上
	//
	//    v6----- v5
	//   /|      /|
	//  v1------v0|        
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v2------v3
	//
	//上图是个规范视域体,它的轴与坐标系轴平行。将物体映射到该视域体中(投影空间)
	//先考虑x轴的，要将其映射在[-1,1]区间内：
	//left <= x <= right;
	//在进行缩放前，将左边归0，即将x坐标减去left即得：
	//0 <= x - left <= right - left;
	//因为想要投影后的区间长度为2[-1,1],而right-left就是映射物体的宽度且肯定大于0
	//不等式同时除以(right-left)可得：
	//0 <= x - left /(right - left) <= 1;再缩放到需要的尺寸(区间长度2)
	//不等式同时乘以2可得：
	//0 <= 2(x - left) / (right - left) <= 2;
	//因为区间为[-1,1]，所以不等式再次减去1可得：
	//-1 <= 2x - right - left / (right - left) <= 1;
	//上面的式子的中间部分就是将3d空间中的x转换到规范视域体的最终算式，可得
	//x' = 2x / (right - left) - [(right + left) / (right - left)];


	//再来计算y轴的，同理可得
	//-1 <= 2y - (top - bottom) / (top - bottom) <= 1;
	//y' = 2y / (top - bottom) - [(top + bottom) / (top - bottom)];


	//再来计算z轴的，D3D标准为[0,1]OpenGL标准为[-1,1]，采用D3D标准所以
	//near <= z <= far;
	//不等式减去near可得：
	//0 <= z - near <= far - near;
	//因为far - near肯定大于0的，所以不等式同时除以 far - near 可得：
	// 0 <= z - near / (far - near) <= 1;
	// z' = z - near / far - near;
	//写成矩阵形式:(right = R, left = L, top = T, bottom = B, far = F, near = N)
	// |  2/(R-L)     0      0       -(R+L)/(R-L) |
	// |  0        2/(T-B)   0       -(T+B)/(T-B) |
	// |  0           0    1/(F-N)   -N/(F-N) |
	// |  0           0      0          1         |
	//这里转置下就行了
	// | 2(R-L)         0            0               0 |
	// |   0           2/(T-B)       0               0 |
	// |   0            0            1/(F-N)         0 |
	// | -(R+L)/(R-L)  -(T+B)/(T-B)  -N/(F-N)        1 |
	LoadIdentity();
	_elements[0] = 2.0f / (right - left);
	
	_elements[5] = 2.0f / (top - bottom);
	_elements[10] = 1.0f / (far - near);

	_elements[12] = -(right + left) / (right - left);
	_elements[13] = -(top + bottom) / (top - bottom);
	_elements[14] = -near / (far - near);
}

void Matrix4x4::SetPerspective(float fovy, float aspect, float near, float far)
{
	//推导过程： 左手坐标系
	//              ▴ y
	//              │         
	//              │        
	//              │           ↗
	//              │         ↗
	//              |       ↗
	//              |     ↗ 
	//              |   ↗ |
	//              | ↗a/2| h/2
	//              ――――n――|――――――――――――▸z
	//               ↘ a/2|
	//                 ↘  | h/2
	//                   ↘|
	//                      ↘
	//                        ↘
	//角度转弧度
	fovy *= (float)M_PI / 180;
	float top = near * tanf(fovy / 2.0f);
	float bottom = -top;
	float left = aspect * bottom;
	float right = aspect * top;

	SetPerspective(left, right, bottom, top, near, far);
}

void Matrix4x4::SetPerspective(float left, float right, float bottom, float top, float near, float far)
{
	//推导过程： 左手坐标系
	//              ▴ y
	//              │         
	//              │        
	//              │           
	//              │         
	//              |       
	//              |     
	//              |   
	//              |           (0,0,n)          (0,0,z)
	//      (0,0,0) ――――――――――――|――――――――――――――― |―――――▸z
	//               ↘  ↘     |L2              |
	//                 ↘   ↘  |(x',y',z')      | L1
	//                   ↘     ↘               |
	//                      ↘      ↘           |
	//                        ↘x        ↘      |
	//                                       ↘  |  (x,y,z)
	//
	//
	//由图可得：L2/L1 = n/z
	//所以 x' / x = n / z; y' / y = n / z; ===>  x' = x * n / z; y' = y * n / z;（1）
	//同样，把坐标映射到规范视域体中的推导如正交投影公式一样
	//x'' = 2*x' / (right - left) - [(right + left) / (right - left)];
	//y'' = 2*y' / (top - bottom) - [(top + bottom) / (top - bottom)];
	//把公式中的x'换成（1）中的x'可得：
	// x'' = 2*n / (right - left) * x / z - [(right + left) / (right - left)]
	//把公式中的y'换成（1）中的y'可得：
	//y'' = 2*n / (top - bottom) * y / z - [(top - bottom) / (top + bottom)]
	//同时乘以z可得：
	// x''* z = 2*n / (right - left) * x - [(right + left) / (right - left)] * z;
	// y'' * z = 2*n / (top - bottom) * y - [ (top + bottom) / (top - bottom)] * z;
	// 为了把这些等式写进矩阵中，需要写成这种形式：
	//x'' = c1*x + c2*y + c3*z + c4; y'' = c5*x + c6*y + c7*z + c8;
	//如果能找到办法获得z'*z的公式， 就可以写一个变换矩阵把(x,y,z)映射到(x''*z, y''*z, z''*z)
	//然后只要把各个部分除以点z，就会得到想要的(x'',y'',z'').

	//我们假设z''*z = p*z + q;（2） (z=n时z''=0, z=f时z''=1),D3D标准z的范围[0,1];代入可得：
	//0 = p*n + q; ==>q = -p*n
	//f = p*f + q; ==> f = p*f - p*n ==> f = p*(f-n); ==> p = f/(f-n); ==> q = -nf/(f-n);
	//代入公式（2）中可得：z''*z = f/f-n * z - f*n/f-n;
	//整理可得：
	// x'' * z = 2*n / (right-left)*x - (right+left / right-left);
	//y'' * z = 2*n / (top-bottom)*y - (top+bottom / top-bottom);
	//z'' * z = f/f-n * z - (f*n / f-n);
	//w'' * z = 1 * z;
	//得到矩阵:(right = R, left = L, top = T, bottom = B, far = F, near = N)
	// |2*N/R-L     0       -(R+L)/(R-L)       0|
	// |0          2*N/T-B  -(T+B)/(T-B)       0|
	// |0           0       F/F-N       -F*N/F-N|
	// |0           0         1                0|

	//转置下：
	// |2*N/R-L       0              0          0|
	// |0             2*N/T-B        0          0|
	// |-(R+L)/(R-L)  -(T+B)/(T-B)   F/F-N      1|
	// |0             0              -F*N/F-N   0|


	LoadZero();
	_elements[0] = 2 * near / right - left;
	_elements[5] = 2 * near / top - bottom;
	_elements[8] = -(right + left) / right - left;
	_elements[9] = -(top + bottom) / top - bottom;
	_elements[10] = far / far - near;
	_elements[11] = 1;
	_elements[14] = -far * near / far - near;
}

void Matrix4x4::SetTranslationPart(const _Vector3D& v3)
{
	_elements[12] = v3.GetX();
	_elements[13] = v3.GetY();
	_elements[14] = v3.GetZ();
}

void Matrix4x4::SetRotationEuler(const double angleX, const double angleY, const double angleZ)
{
	LoadIdentity();
	SetRotationPartEuler(angleX, angleY, angleZ);
}

void Matrix4x4::SetRotationPartEuler(const _Vector3D& v3)
{
	SetRotationPartEuler((double)v3.GetX(), (double)v3.GetY(), (double)v3.GetZ());
}

void Matrix4x4::SetRotationPartEuler(const double angleX, const double angleY, const double angleZ)
{
	//绕欧拉角旋转 就是把 绕x轴旋转a角度， 绕y轴旋转b角度，绕z轴旋转c角度 所推导的3个矩阵
	//按照旋转顺序 X-Y-Z, X-Z-Y, Y-Z-X 矩阵相乘 即可
	//我们按照Z-Y-X顺序来
	double cosX = cos(M_PI * angleX / 180);
	double sinX = sin(M_PI * angleX / 180);

	double cosY = cos(M_PI * angleY / 180);
	double sinY = sin(M_PI * angleY / 180);

	double cosZ = cos(M_PI * angleZ / 180);
	double sinZ = sin(M_PI * angleZ / 180);

	_elements[0] = (float)(cosY * cosZ);
	_elements[1] = (float)(cosY * sinZ);
	_elements[2] = (float)(-sinY);

	double sinXY = sinX * sinY;
	double cosX_sinY = cosX * sinY;

	_elements[4] = (float)(sinXY * cosZ - cosX * sinZ);
	_elements[5] = (float)(sinXY * sinZ + cosX * cosZ);
	_elements[6] = (float)(sinX * cosY);
	_elements[8] = (float)(cosX_sinY * cosZ + sinX * sinZ);
	_elements[9] = (float)(cosX_sinY * sinZ - sinX * cosZ);
	_elements[10] = (float)(cosX * cosY);
}


bool Matrix4x4::operator!=(const Matrix4x4& matrix) const
{
	return !((*this) == matrix);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& matrix) const
{
	return Matrix4x4(_elements[0] - matrix._elements[0],
		_elements[1] - matrix._elements[1],
		_elements[2] - matrix._elements[2],
		_elements[3] - matrix._elements[3],
		_elements[4] - matrix._elements[4],
		_elements[5] - matrix._elements[5],
		_elements[6] - matrix._elements[6],
		_elements[7] - matrix._elements[7],
		_elements[8] - matrix._elements[8],
		_elements[9] - matrix._elements[9],
		_elements[10] - matrix._elements[10],
		_elements[11] - matrix._elements[11],
		_elements[12] - matrix._elements[12],
		_elements[13] - matrix._elements[13],
		_elements[14] - matrix._elements[14],
		_elements[15] - matrix._elements[15]);
}

void Matrix4x4::operator-=(const Matrix4x4& matrix)
{
	(*this) = (*this) - matrix;
}

Matrix4x4 Matrix4x4::operator-() const
{
	Matrix4x4 result(*this);
	for (int i = 0; i < 16; i++)
	{
		result._elements[i] = -result._elements[i];
	}

	return result;
}

void Matrix4x4::operator/=(const float v)
{
	if (FLT_IS_ZERO(v))
	{
		return;
	}

	(*this) = (*this) / v;
}

_Vector4D Matrix4x4::operator*=(const _Vector4D& v4) const
{
	//主要是为了减少乘法运算
	if (_elements[3] == 0.0f && 
		_elements[7] == 0.0f && 
		_elements[11] == 0.0f && 
		_elements[15] == 1.0f)
	{
		return _Vector4D(
				_elements[0] * v4.GetX() + _elements[4] * v4.GetY() + _elements[8] * v4.GetZ() + _elements[12] * v4.GetW(), 
				_elements[1] * v4.GetX() + _elements[5] * v4.GetY() + _elements[9] * v4.GetZ() + _elements[13] * v4.GetW(), 
				_elements[2] * v4.GetX() + _elements[6] * v4.GetY() + _elements[10] * v4.GetZ() + _elements[14] * v4.GetW(),
				v4.GetW()
			);
	}

	return _Vector4D(
		_elements[0] * v4.GetX() + _elements[4] * v4.GetY() + _elements[8] * v4.GetZ() + _elements[12] * v4.GetW(),
		_elements[1] * v4.GetX() + _elements[5] * v4.GetY() + _elements[9] * v4.GetZ() + _elements[13] * v4.GetW(),
		_elements[2] * v4.GetX() + _elements[6] * v4.GetY() + _elements[10] * v4.GetZ() + _elements[14] * v4.GetW(),
		_elements[3] * v4.GetX() + _elements[7] * v4.GetY() + _elements[11] * v4.GetZ() + _elements[15] * v4.GetW()
		);
}

void Matrix4x4::operator*=(const float v)
{
	(*this) = (*this) * v;
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	(*this) = (*this) * matrix;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix) const
{
	return Matrix4x4(
		(matrix._elements[0] * _elements[0] +
		matrix._elements[1] * _elements[4] +
		matrix._elements[2] * _elements[8] +
		matrix._elements[3] * _elements[12]
		),
		(matrix._elements[0] * _elements[1] +
		matrix._elements[1] * _elements[5] +
		matrix._elements[2] * _elements[9] +
		matrix._elements[3] * _elements[13]
		),
		(matrix._elements[0] * _elements[2] +
		matrix._elements[1] * _elements[6] +
		matrix._elements[2] * _elements[10] +
		matrix._elements[3] * _elements[14]
		),
		(matrix._elements[0] * _elements[3] +
		matrix._elements[1] * _elements[7] +
		matrix._elements[2] * _elements[11] +
		matrix._elements[3] * _elements[15]),



		(matrix._elements[4] * _elements[0] +
		matrix._elements[5] * _elements[4] +
		matrix._elements[6] * _elements[8] +
		matrix._elements[7] * _elements[12]
		),
		(matrix._elements[4] * _elements[1] +
		matrix._elements[5] * _elements[5] +
		matrix._elements[6] * _elements[9] +
		matrix._elements[7] * _elements[13]
		),
		(matrix._elements[4] * _elements[2] +
		matrix._elements[5] * _elements[6] +
		matrix._elements[6] * _elements[10] +
		matrix._elements[7] * _elements[14]
		),
		(matrix._elements[4] * _elements[3] +
		matrix._elements[5] * _elements[7] +
		matrix._elements[6] * _elements[11] +
		matrix._elements[6] * _elements[15]
		),


		(matrix._elements[8] * _elements[0] +
		matrix._elements[9] * _elements[4] +
		matrix._elements[10] * _elements[8] +
		matrix._elements[11] * _elements[12]
		),
		(matrix._elements[8] * _elements[1] +
		matrix._elements[9] * _elements[5] +
		matrix._elements[10] * _elements[9] +
		matrix._elements[11] * _elements[13]
		),
		(matrix._elements[8] * _elements[2] +
		matrix._elements[9] * _elements[6] +
		matrix._elements[10] * _elements[10] +
		matrix._elements[11] * _elements[14]
		),
		(matrix._elements[8] * _elements[3] +
		matrix._elements[9] * _elements[7] +
		matrix._elements[10] * _elements[11] +
		matrix._elements[11] * _elements[15]
		),

		(matrix._elements[12] * _elements[0] +
		matrix._elements[13] * _elements[4] +
		matrix._elements[14] * _elements[8] +
		matrix._elements[15] * _elements[12]
		),
		(matrix._elements[12] * _elements[1] +
		matrix._elements[13] * _elements[5] +
		matrix._elements[14] * _elements[9] +
		matrix._elements[15] * _elements[13]
		),
		(matrix._elements[12] * _elements[2] +
		matrix._elements[13] * _elements[6] +
		matrix._elements[14] * _elements[10] +
		matrix._elements[15] * _elements[14]
		),
		(matrix._elements[12] * _elements[3] +
		matrix._elements[13] * _elements[7] +
		matrix._elements[14] * _elements[11] +
		matrix._elements[15] * _elements[15]
		)

		);
}

Matrix4x4 Matrix4x4::operator*(const float v) const
{
	return Matrix4x4(_elements[0] * v,
		_elements[1] * v,
		_elements[2] * v,
		_elements[3] * v,
		_elements[4] * v,
		_elements[5] * v,
		_elements[6] * v,
		_elements[7] * v,
		_elements[8] * v,
		_elements[9] * v,
		_elements[10] * v,
		_elements[11] * v,
		_elements[12] * v,
		_elements[13] * v,
		_elements[14] * v,
		_elements[15] * v);
}

_Vector4D Matrix4x4::operator*(const _Vector4D& v4) const
{
	//平移部分为0，w为1
	if (FLT_EQUAL(_elements[3], 0.0f) &&
		FLT_EQUAL(_elements[7], 0.0f) &&
		FLT_EQUAL(_elements[11], 0.0f) &&
		FLT_EQUAL(_elements[15], 1.0f))
	{
		return _Vector4D(
			_elements[0] * v4.GetX() + 
			_elements[4] * v4.GetY() + 
			_elements[8] * v4.GetZ() + 
			_elements[12] * v4.GetW(),

			_elements[1] * v4.GetX() + 
			_elements[5] * v4.GetY() +
			_elements[9] * v4.GetZ() +
			_elements[13] * v4.GetW(),

			_elements[2] * v4.GetX() + 
			_elements[6] * v4.GetY() +
			_elements[10] * v4.GetZ() +
			_elements[14] * v4.GetW(),

			v4.GetW()
			);
	}

	return _Vector4D(
		_elements[0] * v4.GetX() +
		_elements[4] * v4.GetY() +
		_elements[8] * v4.GetZ() +
		_elements[12] * v4.GetW(),

		_elements[1] * v4.GetX() +
		_elements[5] * v4.GetY() +
		_elements[9] * v4.GetZ() +
		_elements[13] * v4.GetW(),

		_elements[2] * v4.GetX() +
		_elements[6] * v4.GetY() +
		_elements[10] * v4.GetZ() +
		_elements[14] * v4.GetW(),

		_elements[3] * v4.GetX() +
		_elements[7] * v4.GetY() +
		_elements[11] * v4.GetZ() +
		_elements[15] * v4.GetW()
		);
}

bool Matrix4x4::operator==(const Matrix4x4& matrix) const
{
	for (int i = 0; i < 16; i++)
	{
		if (!FLT_EQUAL(_elements[i], matrix._elements[i]))
		{
			return false;
		}
	}

	return true;
}

Matrix4x4 Matrix4x4::operator/(const float v) const
{
	if (FLT_IS_ZERO(v) || 1.0f == v)
	{
		return (*this);
	}

	float factor = 1.0f / v;
	return (*this) * factor;
}

void Matrix4x4::operator+=(const Matrix4x4& matrix)
{
	(*this) = (*this) + matrix;
}

Matrix4x4 operator*(float factor, const Matrix4x4& matrix)
{
	return matrix * factor;
}