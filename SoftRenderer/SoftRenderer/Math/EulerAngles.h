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

	//变化为 限制集 欧拉角
	void canonize();

	//从四元数转换到欧拉角
	//输入的四元数假设为物体--惯性或 惯性--物体四元数
	void fromObjectToInertialQuaternion(const Quaternions& q);
	void frontInertialToObjectQuaternion(const Quaternions& q);

	//从矩阵转换到欧拉角
	//输入矩阵假设为物体---世界 或 世界---物体转换矩阵
	//平移部分被省略，并且假设矩阵是正交的
	void fromObjectToWorldMatrix(const Matrix4x4& mat);
	void fromWorldToObjectMatrix(const Matrix4x4& mat);

	//从旋转矩阵转换到欧拉角
	void fromRotationMatrix(const RotationMatrix* rotateMat);

	//直接的表示方式
	//用弧度保存三个角度
	float heading;
	float pitch;
	float bank;
};

//全局的 单位 欧拉角
extern const EulerAngles kEulerAnglesIdentity;

#endif