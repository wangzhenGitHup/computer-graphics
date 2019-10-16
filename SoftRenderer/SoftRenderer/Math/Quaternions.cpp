#include "Quaternions.h"
#include "SelfMaths.h"

void QuatZero(QuaternionsUnion* pQuat)
{
	pQuat->_x = pQuat->_y = pQuat->_z = pQuat->_w = 0.0f;
}

void QuatInitWXYZ(QuaternionsUnion* pQuat, float w, float x, float y, float z)
{
	pQuat->_w = w;
	pQuat->_x = x;
	pQuat->_y = y;
	pQuat->_z = z;
}

void QuatInitVector3D(QuaternionsUnion* pQuat, const _Vector3D& vec)
{
	pQuat->_w = 0;
	pQuat->_x = vec.GetX();
	pQuat->_y = vec.GetY();
	pQuat->_z = vec.GetZ();
}

void QuatInit(QuaternionsUnion* srcQuat, QuaternionsUnion* dstQuat)
{
	srcQuat->_w = dstQuat->_w;
	srcQuat->_x = dstQuat->_x;
	srcQuat->_y = dstQuat->_y;
	srcQuat->_z = dstQuat->_z;
}

void QuatCopy(QuaternionsUnion* dstQuat, QuaternionsUnion* srcQuat)
{
	dstQuat->_w = srcQuat->_w;
	dstQuat->_x = srcQuat->_x;
	dstQuat->_y = srcQuat->_y;
	dstQuat->_z = srcQuat->_z;
}

void Vector3D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector3D& vec, float theta)
{
	//方向向量必须是单位向量，角度的单位为弧度
	float theta_div_2 = (0.5f) * theta;

	//计算四元数
	//TODO:

	float sinf_theta = sinf(theta_div_2);

	pQuat->_x = sinf_theta * vec.GetX();
	pQuat->_y = sinf_theta * vec.GetY();
	pQuat->_z = sinf_theta * vec.GetZ();
	pQuat->_w = cosf(theta_div_2);
}

void Vector4D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector4D& vec, float theta)
{

}

void EulerZYX_To_Quat(QuaternionsUnion* pQuat, float theta_z, float theta_y, float thetz_x)
{
	float cos_z_2 = 0.5f * cosf(theta_z);
	float cos_y_2 = 0.5f * cosf(theta_y);
	float cos_x_2 = 0.5f * cosf(thetz_x);

	float sin_z_2 = 0.5f * sinf(theta_z);
	float sin_y_2 = 0.5f * sinf(theta_y);
	float sin_x_2 = 0.5f * sinf(thetz_x);

	//计算四元数
	pQuat->_w = cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
	pQuat->_x = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
	pQuat->_y = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
	pQuat->_z = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;
}

void Quat_To_Vector3D_Theta(const QuaternionsUnion& pQuat, _Vector3D& vec, float& theta)
{
	//提取角度
	theta = acosf(pQuat._w);

	float sinf_theta_inv = 1.0f / sinf(theta);

	vec.SetX(pQuat._x * sinf_theta_inv);
	vec.SetY(pQuat._y * sinf_theta_inv);
	vec.SetZ(pQuat._z * sinf_theta_inv);

	theta *= 2.0f;

}

void Quat_Add(const QuaternionsUnion& pQuat1,
	const QuaternionsUnion& pQuat2,
	QuaternionsUnion& pResult)
{

}

void Quat_Sub(const QuaternionsUnion& pQuat1,
	const QuaternionsUnion& pQuat2,
	QuaternionsUnion& pResult)
{

}

void Quat_Mul(const QuaternionsUnion& pQuat1,
	const QuaternionsUnion& pQuat2,
	QuaternionsUnion& pResult)
{
	float prd_0 = (pQuat1._z - pQuat1._y) * (pQuat2._y - pQuat2._z);
	float prd_1 = (pQuat1._w + pQuat1._x) * (pQuat2._w + pQuat2._x);
	float prd_2 = (pQuat1._w - pQuat1._x) * (pQuat2._y + pQuat2._z);
	float prd_3 = (pQuat1._y + pQuat1._z) * (pQuat2._w - pQuat2._x);
	float prd_4 = (pQuat1._z - pQuat1._x) * (pQuat2._x - pQuat2._y);
	float prd_5 = (pQuat1._z + pQuat1._x) * (pQuat2._x + pQuat2._y);
	float prd_6 = (pQuat1._w + pQuat1._y) * (pQuat2._w - pQuat2._z);
	float prd_7 = (pQuat1._w - pQuat1._y) * (pQuat2._w + pQuat2._z);
	float prd_8 = prd_5 + prd_6 + prd_7;
	float prd_9 = 0.5f * (prd_4 + prd_8);

	pResult._w = prd_0 + prd_9 - prd_5;
	pResult._x = prd_1 + prd_9 - prd_8;
	pResult._y = prd_2 + prd_9 - prd_7;
	pResult._z = prd_3 + prd_9 - prd_6;
}

void Quat_Conjugate(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult)
{

}

void Quat_Scale(QuaternionsUnion& pQuat, float scale)
{

}

float Quat_Length(const QuaternionsUnion& pQuat)
{
	return 0.0f;
}

void Quat_Normalzie(QuaternionsUnion& pQuat)
{

}

void Quat_Unit_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult)
{

}

void Quat_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult)
{

}

void Quat_Triple_Product(const QuaternionsUnion& pQuat1,
	const QuaternionsUnion& pQuat2,
	const QuaternionsUnion& pQuat3,
	QuaternionsUnion& pResult)
{

}
