#ifndef  __EULERANGLES__H__
#define  __EULERANGLES__H__

class Quaternions;
class Matrix4x4;
class RotationMatrix;

class EulerAngles
{
public:
	EulerAngles(){}
	EulerAngles(float h, float p, float b) : heading(h), pitch(p), bank(b){}

	void Identity(){ pitch = bank = heading = 0.0f; }

	//�仯Ϊ ���Ƽ� ŷ����
	void canonize();

	//����Ԫ��ת����ŷ����
	//�������Ԫ������Ϊ����--���Ի� ����--������Ԫ��
	void fromObjectToInertialQuaternion(const Quaternions& q);
	void frontInertialToObjectQuaternion(const Quaternions& q);

	//�Ӿ���ת����ŷ����
	//����������Ϊ����---���� �� ����---����ת������
	//ƽ�Ʋ��ֱ�ʡ�ԣ����Ҽ��������������
	void fromObjectToWorldMatrix(const Matrix4x4& mat);
	void fromWorldToObjectMatrix(const Matrix4x4& mat);

	//����ת����ת����ŷ����
	void fromRotationMatrix(const RotationMatrix* rotateMat);

	//ֱ�ӵı�ʾ��ʽ
	//�û��ȱ��������Ƕ�
	float heading;
	float pitch;
	float bank;
};

//ȫ�ֵ� ��λ ŷ����
extern const EulerAngles kEulerAnglesIdentity;

#endif