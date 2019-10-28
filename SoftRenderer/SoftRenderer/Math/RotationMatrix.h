#ifndef  __ROTATIONMATRIX__H__
#define  __ROTATIONMATRIX__H__


class EulerAngles;
class Quaternions;
class _Vector3D;

class RotationMatrix
{
public:
	void Identity();

	//根据指定的方位构造矩阵
	void setup(const EulerAngles& orientation);
	//根据四元数构造矩阵，假设该四元数参数代表指定方向的变化
	void fromInertialToObjectQuaternion(const Quaternions& q);
	void fromObjectToInertialQuaternion(const Quaternions& q);
	//执行旋转
	_Vector3D inertialToObject(const _Vector3D& vec3)const;
	_Vector3D objectToInertial(const _Vector3D& vec3)const;


	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
};


#endif