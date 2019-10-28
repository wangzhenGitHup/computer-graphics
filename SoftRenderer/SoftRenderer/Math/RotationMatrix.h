#ifndef  __ROTATIONMATRIX__H__
#define  __ROTATIONMATRIX__H__


class EulerAngles;
class Quaternions;
class _Vector3D;

class RotationMatrix
{
public:
	void Identity();

	//����ָ���ķ�λ�������
	void setup(const EulerAngles& orientation);
	//������Ԫ��������󣬼������Ԫ����������ָ������ı仯
	void fromInertialToObjectQuaternion(const Quaternions& q);
	void fromObjectToInertialQuaternion(const Quaternions& q);
	//ִ����ת
	_Vector3D inertialToObject(const _Vector3D& vec3)const;
	_Vector3D objectToInertial(const _Vector3D& vec3)const;


	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
};


#endif