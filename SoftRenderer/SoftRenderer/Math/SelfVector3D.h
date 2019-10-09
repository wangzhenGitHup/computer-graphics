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
	//加载零向量
	void LoadZero();
	//加载单位向量
	void LoadOne();
	//归一化向量
	void Normalized();
	//得到向量的模
	float GetLength()const;
	//得到向量的模的平方
	float GetSquaredLength()const;
	//得到归一化向量
	_Vector3D GetNormalized()const;
	//线性插值计算
	_Vector3D Lerp(const _Vector3D& v3, float factor)const;

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

	//正负向量
	_Vector3D operator-()const;
	_Vector3D operator+()const;

	//强制转换
	operator float*()const{ return (float*)this; }
	operator const float*() const{ return (const float*)this; }

	//点乘
	float Dot(const _Vector3D& v3)const;

	//叉乘
	_Vector3D Cross(const _Vector3D& vec)const;

	//向量操作

	//绕X轴旋转
	void RotateX(double angle);
	_Vector3D GetRotatedX(double angle)const;

	//绕Y轴旋转
	void RotateY(double angle);
	_Vector3D GetRotatedY(double angle)const;

	//绕Z轴旋转
	void RotateZ(double angle);
	_Vector3D GetRotatedZ(double angle)const;

	//绕任意轴旋转
	void RotateAxis(double angle, const _Vector3D& axis);
	_Vector3D GetRotatedAxis(double angle, const _Vector3D& axis)const;

	void PackTo01(); //pack to [0, 1] for color
	_Vector3D GetPackedTo01()const;

	//比较
	bool operator==(const _Vector3D& v3)const;
	bool operator!=(const _Vector3D& v3)const;

private:
	float _x;
	float _y;
	float _z;
};
#endif