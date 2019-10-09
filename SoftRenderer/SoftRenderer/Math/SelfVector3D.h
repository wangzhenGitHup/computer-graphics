#ifndef  __SELF_VECTOR3D__H__
#define  __SELF_VECTOR3D__H__

class _Vector3D
{
public:
	_Vector3D() : _x(0.0f), _y(0.0f), _z(0.0f){}
	_Vector3D(float x, float y, float z) : _x(x), _y(y), _z(z){}
	_Vector3D(const _Vector3D& v3) : _x(v3._x), _y(v3._y), _z(v3._z){}
	~_Vector3D(){}

	void Set(float x, float y, float z);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	float GetX()const{ return _x; }
	float GetY()const{ return _y; }
	float GetZ()const{ return _z; }
	//����������
	void LoadZero();
	//���ص�λ����
	void LoadOne();
	//��һ������
	void Normalized();
	//�õ�������ģ
	float GetLength()const;
	//�õ�������ģ��ƽ��
	float GetSquaredLength()const;
	//�õ���һ������
	_Vector3D GetNormalized()const;
	//���Բ�ֵ����
	_Vector3D Lerp(const _Vector3D& v3, float factor)const;

	//��������
	_Vector3D operator+(const _Vector3D& v3)const;
	_Vector3D operator-(const _Vector3D& v3)const;
	_Vector3D operator*(const float v)const;
	_Vector3D operator/(const float v)const;
	void operator+=(const _Vector3D& v3);
	void operator-=(const _Vector3D& v3);
	void operator*=(const float v);
	void operator/=(const float v);
	friend _Vector3D operator*(float v, const _Vector3D& v3);

	//��������
	_Vector3D operator-()const;
	_Vector3D operator+()const;

	//ǿ��ת��
	operator float*()const{ return (float*)this; }
	operator const float*() const{ return (const float*)this; }

	//���
	float Dot(const _Vector3D& v3)const;

	//���
	_Vector3D Cross(const _Vector3D& vec)const;

	//��������

	//��X����ת
	void RotateX(double angle);
	_Vector3D GetRotatedX(double angle)const;

	//��Y����ת
	void RotateY(double angle);
	_Vector3D GetRotatedY(double angle)const;

	//��Z����ת
	void RotateZ(double angle);
	_Vector3D GetRotatedZ(double angle)const;

	//����������ת
	void RotateAxis(double angle, const _Vector3D& axis);
	_Vector3D GetRotatedAxis(double angle, const _Vector3D& axis)const;

	void PackTo01(); //pack to [0, 1] for color
	_Vector3D GetPackedTo01()const;

	//�Ƚ�
	bool operator==(const _Vector3D& v3)const;
	bool operator!=(const _Vector3D& v3)const;

private:
	float _x;
	float _y;
	float _z;
};
#endif