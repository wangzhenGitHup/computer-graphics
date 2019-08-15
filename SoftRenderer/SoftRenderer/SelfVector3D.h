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
	void LoadZero();
	void LoadOne();
	void Normalized();
	float GetLength()const;
	_Vector3D GetNormalized()const;

	//线性插值计算
	_Vector3D Lerp(const _Vector3D& v3, float factor)const;
	_Vector3D QuadraticInterpolate(const _Vector3D& a, const _Vector3D& b, float factor);

	//四则运算
	_Vector3D operator+(const _Vector3D& v3)const;
	_Vector3D operator-(const _Vector3D& v3)const;
	_Vector3D operator*(const float v)const;
	_Vector3D operator/(const float v)const;
	void operator+=(const _Vector3D& v3);
	void operator-=(const _Vector3D& v3);
	void operator*=(const float v);
	void operator/=(const float v);
	friend _Vector3D operator*(float v, const _Vector3D& v3);
	void Add(const _Vector3D& src, _Vector3D& dst);
	void Subtract(const _Vector3D& src, _Vector3D& dst);

	//正负向量
	_Vector3D operator-()const;
	_Vector3D operator+()const;

	//强制转换
	operator float*()const{ return (float*)this; }
	operator const float*() const{ return (const float*)this; }

	//点乘
	float Dot(const _Vector3D& a, const _Vector3D& b);

	//叉乘
	_Vector3D Cross(const _Vector3D& a, const _Vector3D& b);

	//向量操作
	void RotateX(double angle);
	void RotateY(double angle);
	void RotateZ(double angle);
	void RotateAxis(double angle, const _Vector3D& axis);

private:
	float _x;
	float _y;
	float _z;
};
#endif