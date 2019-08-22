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

	//��λ����
	void LoadIdentity();
	//���ø���λ�õ�Ԫ��
	void SetElement(int pos, float v);
	//�õ�����λ�õ�Ԫ��
	float GetElement(int pos)const;
	//�õ�����λ�õ�һ������
	_Vector4D GetRow(int pos)const;
	//�õ�����λ�õ�һ������
	_Vector4D GetColumn(int pos)const;
	//���������
	void LoadZero();

	//��������
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

	//�Ƚ�����
	bool operator==(const Matrix4x4& matrix)const;
	bool operator!=(const Matrix4x4& matrix)const;

	//��������
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

	//�����
	void Inverse();
	Matrix4x4 GetInverse()const;

	//ת�þ���
	void Transpose();
	Matrix4x4 GetTranspose()const;

	//��ת�ú���
	void InverseTranspose();
	Matrix4x4 GetInverseTranspose()const;

	//���������
	void AffineInverse();
	Matrix4x4 GetAffineInverse()const;

	//������ת�þ���
	void AffineInverseTranspose();
	Matrix4x4 GetAffineInverseTranspose();

	//ƽ��
	void SetTranslation(const _Vector3D& translation);
	//����
	void SetScale(const _Vector3D& v3);
	//ͳһ����
	void SetUniformScale(const float factor);
	//�Ƹ�����������ת
	void SetRotationAxis(const double angle, const _Vector3D& axis);
	//��X����ת
	void SetRotationX(const double angle);
	//��Y����ת
	void SetRotationY(const double angle);
	//��Z����ת
	void SetRotationZ(const double angle);
	//�Ƹ�����ŷ������ת
	void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
	//��������
	void SetOrtho(float left, float right, float bottom, float top, float near, float far);
	//ͶӰ����
	void SetPerspective(float fovy, float aspect, float near, float far);
	void SetPerspective(float left, float righ, float bottom, float top, float near, float far);
	//���þ����ŵ�ƽ�ƺ���ת
	void SetTranslationPart(const _Vector3D& v3);
	void SetRotationPartEuler(const double angleX, const double angleY, const double angleZ);
	void SetRotationPartEuler(const _Vector3D& v3);

	//ǿ������ת��
	operator float*()const{ return (float*)this; }
	operator const float*()const{ return (const float*)this; }


private:
	float _elements[16];
};

#endif