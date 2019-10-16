#ifndef  __QUATERNIONS__H__
#define  __QUATERNIONS__H__

#include "SelfVector3D.h"
#include "SelfVector4D.h"

//三种访问四元数的方式
union QuaternionsUnion
{
	//数组方式访问
	float elements[4]; //按w, x, y, z的顺序以数组方式存储

	//以浮点数和向量的方式访问
	struct
	{
		float q0; //实部
		_Vector3D qv; //虚部(x*i + y*j + z*k)
	};

	//显示名称访问
	struct
	{
		float _x;
		float _y;
		float _z;
		float _w;
	};
};

//四元数
class Quaternions
{
public:


private:
	QuaternionsUnion _data;
};

void QuatZero(QuaternionsUnion* pQuat);
void QuatInitWXYZ(QuaternionsUnion* pQuat, float w, float x, float y, float z);
void QuatInitVector3D(QuaternionsUnion* pQuat, const _Vector3D& vec);
void QuatInit(QuaternionsUnion* srcQuat, QuaternionsUnion* dstQuat);
void QuatCopy(QuaternionsUnion* dstQuat, QuaternionsUnion* srcQuat);

//根据方向向量和角度创建一个旋转的四元数, 方向向量必须是单位向量, 4D向量丢弃w分量
void Vector3D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector3D& vec, float theta);

void Vector4D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector4D& vec, float theta);

//根据绕z，y，x旋转的欧拉角创建一个旋转的四元数
void EulerZYX_To_Quat(QuaternionsUnion* pQuat, float theta_z, float theta_y, float thetz_x);

//将一个单位四元数转换为一个单位方向向量和一个绕该向量旋转的角度
void Quat_To_Vector3D_Theta(const QuaternionsUnion& pQuat, _Vector3D& vec, float& theta);

//四元数相加
void Quat_Add(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);
//相减
void Quat_Sub(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);
//乘
void Quat_Mul(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);

//共轭
void Quat_Conjugate(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//缩放
void Quat_Scale(QuaternionsUnion& pQuat, float scale);

//返回四元数的长度
float Quat_Length(const QuaternionsUnion& pQuat);

//归一化四元数
void Quat_Normalzie(QuaternionsUnion& pQuat);

//求四元数的逆(pQuat必须为单位四元数)
void Quat_Unit_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//对非单位四元数求逆
void Quat_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//将3个四元素相乘
void Quat_Triple_Product(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, const QuaternionsUnion& pQuat3, QuaternionsUnion& pResult);

#endif