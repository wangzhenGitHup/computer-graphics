#ifndef  __QUATERNIONS__H__
#define  __QUATERNIONS__H__

#include "SelfVector3D.h"
#include "SelfVector4D.h"

//���ַ�����Ԫ���ķ�ʽ
union QuaternionsUnion
{
	//���鷽ʽ����
	float elements[4]; //��w, x, y, z��˳�������鷽ʽ�洢

	//�Ը������������ķ�ʽ����
	struct
	{
		float q0; //ʵ��
		_Vector3D qv; //�鲿(x*i + y*j + z*k)
	};

	//��ʾ���Ʒ���
	struct
	{
		float _x;
		float _y;
		float _z;
		float _w;
	};
};

//��Ԫ��
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

//���ݷ��������ͽǶȴ���һ����ת����Ԫ��, �������������ǵ�λ����, 4D��������w����
void Vector3D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector3D& vec, float theta);

void Vector4D_Theta_To_Quat(QuaternionsUnion* pQuat, const _Vector4D& vec, float theta);

//������z��y��x��ת��ŷ���Ǵ���һ����ת����Ԫ��
void EulerZYX_To_Quat(QuaternionsUnion* pQuat, float theta_z, float theta_y, float thetz_x);

//��һ����λ��Ԫ��ת��Ϊһ����λ����������һ���Ƹ�������ת�ĽǶ�
void Quat_To_Vector3D_Theta(const QuaternionsUnion& pQuat, _Vector3D& vec, float& theta);

//��Ԫ�����
void Quat_Add(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);
//���
void Quat_Sub(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);
//��
void Quat_Mul(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, QuaternionsUnion& pResult);

//����
void Quat_Conjugate(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//����
void Quat_Scale(QuaternionsUnion& pQuat, float scale);

//������Ԫ���ĳ���
float Quat_Length(const QuaternionsUnion& pQuat);

//��һ����Ԫ��
void Quat_Normalzie(QuaternionsUnion& pQuat);

//����Ԫ������(pQuat����Ϊ��λ��Ԫ��)
void Quat_Unit_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//�Էǵ�λ��Ԫ������
void Quat_Inverse(const QuaternionsUnion& pQuat, QuaternionsUnion& pResult);

//��3����Ԫ�����
void Quat_Triple_Product(const QuaternionsUnion& pQuat1, const QuaternionsUnion& pQuat2, const QuaternionsUnion& pQuat3, QuaternionsUnion& pResult);

#endif