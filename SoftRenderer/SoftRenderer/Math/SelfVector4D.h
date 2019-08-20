#ifndef  __SELF__VECTOR4D__H__
#define  __SELF__VECTOR4D__H__

#include "SelfVector3D.h"

class _Vector4D
{
public:
	_Vector4D() : _x(0.0f), _y(0.0f), _z(0.0f), _w(0.0f){}
	_Vector4D(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w){}
	_Vector4D(const _Vector4D& v4) : _x(v4._x), _y(v4._y), _z(v4._z), _w(v4._w){}
	_Vector4D(const _Vector3D& v3) : _x(v3.GetX()), _y(v3.GetY()), _z(v3.GetZ()), _w(1.0f){}
	~_Vector4D(){}

	void Set(float x, float y, float z, float w);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	void SetW(float w);
	float GetX()const{ return _x; }
	float GetY()const{ return _y; }
	float GetZ()const{ return _z; }
	float GetW()const{ return _w; }
	//����������
	void LoadZero();
	//���ص�λ����
	void LoadOne();
	//���Բ�ֵ
	_Vector4D Lerp(const _Vector4D& v4, float factor)const;
	_Vector4D QuadraticInterpolate(const _Vector4D& a, const _Vector4D& b, float factor)const;
	//��һ������
	void Normalized();
	//�õ���һ������
	_Vector3D GetNormalized()const;
	//�õ�������ģ
	float GetLength()const;
	//�õ�������ģ��ƽ��
	float GetSquaredLength()const;

	void RotateX(double angle);
	_Vector4D GetRotateX(double angle)const;
	void RotateY(double angle);
	_Vector4D GetRotateY(double angle)const;
	void RotateZ(double angle);
	_Vector4D GetRotateZ(double angle)const;
	void RotateAxis(double angle, const _Vector3D& axis);
	_Vector4D GetRotateAxis(double angle, const _Vector3D& axis)const;

	//��������
	_Vector4D operator+(const _Vector4D& v4)const;
	_Vector4D operator-(const _Vector4D& v4)const;
	_Vector4D operator*(const float v)const;
	_Vector4D operator/(const float v)const;
	friend _Vector4D operator*(float factor, const _Vector4D& v4);
	void operator+=(const _Vector4D& v4);
	void operator-=(const _Vector4D& v4);
	void operator*=(const float v);
	void operator/=(const float v);

	//�Ƚ��ж�
	bool operator==(const _Vector4D& v4)const;
	bool operator!=(const _Vector4D& v4)const;

	//��������
	_Vector4D operator-()const;
	_Vector4D operator+()const;

	//ǿ������ת��
	operator float*()const{ return (float*) this; }
	operator const float*() const{ return (const float*)this; }
	//ת����3D����
	operator _Vector3D();

	//���
	float Dot(const _Vector4D& a, const _Vector4D& b)const;


private:
	float _x;
	float _y;
	float _z;
	float _w;
};

#endif