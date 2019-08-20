#ifndef  __SELF_VECTOR2D__H__
#define  __SELF_VECTOR2D__H__


class _Vector2D
{
public:
	_Vector2D() : _x(0.0f), _y(0.0f){}
	_Vector2D(float x, float y) : _x(x), _y(y){}
	_Vector2D(const _Vector2D& v2) : _x(v2._x), _y(v2._y){}
	~_Vector2D(){}

	void Set(float x, float y);
	void SetX(float x);
	void SetY(float y);
	float GetX()const;
	float GetY()const;
	//��һ������
	void Normalized();
	//�õ�������ģ
	float GetLength()const;
	//�õ���һ������
	_Vector2D GetNormalized()const;

	//���Բ�ֵ����
	_Vector2D Lerp(const _Vector2D& v2, float factor)const;
	_Vector2D QuadraticInterpolate(const _Vector2D& a, const _Vector2D& b, float factor);

	//��������
	_Vector2D operator*(const float v)const;
	_Vector2D operator/(const float v)const;
	_Vector2D operator+(const _Vector2D& v2)const;
	_Vector2D operator-(const _Vector2D& v2)const;
	void operator+=(const _Vector2D& v2);
	void operator-=(const _Vector2D& v2);
	void operator*=(const float v);
	void operator/=(const float v);
	friend _Vector2D operator*(float factor, const _Vector2D& v2);

	//�Ƚ�
	bool operator==(const _Vector2D& v2)const;
	bool operator!=(const _Vector2D& v2)const;

	//��������
	_Vector2D operator-()const;
	_Vector2D operator+()const;

	//ǿ��ת��
	operator float*() const{ return (float*)this; }
	operator const float*() const{ return (const float*)this;  }

	//���
	float Dot(const _Vector2D& a, const _Vector2D& b)const;

private:
	float _x;
	float _y;
};
#endif