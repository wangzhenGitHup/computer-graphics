#ifndef  __QUATERNIONS__H__
#define  __QUATERNIONS__H__


class _Vector3D;
class EulerAngles;


//��Ԫ��
class Quaternions
{
public:
	void Identity(){ w = 1.0f; x = y = z = 0.0f; }

	//����ִ����ת����Ԫ��
	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const _Vector3D& axis, float theta);

	//����ִ�� ����----����  ��ת����Ԫ������λ������ŷ������ʽ����
	void setToRotateObjectToInertial(const EulerAngles& orientation);
	void setToRotateInertialToObject(const EulerAngles& orientation);

	//���
	Quaternions operator*(const Quaternions& q)const;

	//��ֵ�˷�
	Quaternions& operator*=(const Quaternions& q);

	//����Ԫ�����
	void Normalized();

	//��ȡ��ת�Ǻ���ת��
	float getRotationAngle()const;
	_Vector3D getRotationAxis()const;


	float w, x, y, z;
};

//ȫ�ֵ�λ ��Ԫ��
extern const Quaternions kQuaternionIdentity;

//��Ԫ�����
extern float Dot(const Quaternions& q1, const Quaternions& q2);

//�������Բ�ֵ
extern Quaternions slerp(const Quaternions& q1, const Quaternions& q2, float factor);

//��Ԫ������
extern Quaternions conjugate(const Quaternions& q);

//��Ԫ����
extern Quaternions Pow(const Quaternions& q, float exponent);

#endif