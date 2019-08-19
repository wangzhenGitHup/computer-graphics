#ifndef __SELF__MATRIX4X4__H__
#define __SELF__MATRIX4X4__H__

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

	//µ•Œªæÿ’Û
	void LoadIdentity();

private:
	float _elements[16];
};

#endif