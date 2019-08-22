#ifndef __SELF__MATRIX4X4__H__
#define __SELF__MATRIX4X4__H__


class _Vector3D;
class _Vector4D;

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(float m0, float m1, float m2, float m3,
		float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11,
		float m12, float m13, float m14, float m15);
	Matrix4x4(const float* v);
	Matrix4x4(const Matrix4x4& matrix);
	~Matrix4x4(){}

	//单位矩阵
	void LoadIdentity();
	//设置给定位置的元素
	void SetElement(int pos, float v);
	//得到给定位置的元素
	float GetElement(int pos)const;
	//得到给定位置的一行向量
	_Vector4D GetRow(int pos)const;
	//得到给定位置的一列向量
	_Vector4D GetColumn(int pos)const;
	//加载零矩阵
	void LoadZero();

	//四则运算
	Matrix4x4 operator+(const Matrix4x4& matrix)const;
	Matrix4x4 operator-(const Matrix4x4& matrix)const;
	Matrix4x4 operator*(const Matrix4x4& matrix)const;
	Matrix4x4 operator*(const float v)const;
	_Vector4D operator*(const _Vector4D& v4)const;
	Matrix4x4 operator/(const float v)const;
	void operator+=(const Matrix4x4& matrix);
	void operator-=(const Matrix4x4& matrix);
	void operator*=(const Matrix4x4& matrix);
	void operator*=(const float v);
	void operator/=(const float v);
	_Vector4D operator*=(const _Vector4D& v4)const;
	friend Matrix4x4 operator*(float factor, const Matrix4x4& matrix);

	//比较运算
	bool operator==(const Matrix4x4& matrix)const;
	bool operator!=(const Matrix4x4& matrix)const;

	//正负矩阵
	Matrix4x4 operator-()const;
	Matrix4x4 operator+()const;

	void RotateVector3D(_Vector3D& v3)const;
	void InverseRotateVector3D(_Vector3D& v3)const;
	_Vector3D GetRotatedVector3D(const _Vector3D& v3)const;
	_Vector3D GetInverseRotatedVector3D(const _Vector3D& v3)const;

	void TranslateVector3D(_Vector3D& v3)const;
	void InverseTranslateVector3D(_Vector3D& v3)const;

	_Vector3D GetTranslatedVector3D(const _Vector3D& v3)const;
	_Vector3D GetInverseTranslatedVector3D(const _Vector3D& v3)const;

	//逆矩阵
	void Inverse();
	Matrix4x4 GetInverse()const;

	//转置矩阵
	void Transpose();
	Matrix4x4 GetTranspose()const;

	//逆转置合体
	void InverseTranspose();
	Matrix4x4 GetInverseTranspose()const;

	//仿射逆矩阵
	void AffineInverse();
	Matrix4x4 GetAffineInverse()const;

	//仿射逆转置矩阵
	void AffineInverseTranspose();
	Matrix4x4 GetAffineInverseTranspose();

	//平移
	void SetTranslation(const _Vector3D& translation);
	//缩放
	void SetScale(const _Vector3D& v3);
	//统一缩放
	void SetUniformScale(const float factor);
	//绕给定坐标轴旋转
	void SetRotationAxis(const double angle, const _Vector3D& axis);
	//绕X轴旋转
	void SetRotationX(const double angle);
	//绕Y轴旋转
	void SetRotationY(const double angle);
	//绕Z轴旋转
	void SetRotationZ(const double angle);
	//绕给定的欧拉角旋转
	void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
	//正交矩阵
	void SetOrtho(float left, float right, float bottom, float top, float near, float far);
	//投影矩阵
	void SetPerspective(float fovy, float aspect, float near, float far);
	void SetPerspective(float left, float righ, float bottom, float top, float near, float far);
	//设置矩阵部门的平移和旋转
	void SetTranslationPart(const _Vector3D& v3);
	void SetRotationPartEuler(const double angleX, const double angleY, const double angleZ);
	void SetRotationPartEuler(const _Vector3D& v3);

	//强制类型转换
	operator float*()const{ return (float*)this; }
	operator const float*()const{ return (const float*)this; }


private:
	float _elements[16];
};

#endif