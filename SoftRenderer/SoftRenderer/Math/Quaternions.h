#ifndef  __QUATERNIONS__H__
#define  __QUATERNIONS__H__


class _Vector3D;
class EulerAngles;


//四元数
class Quaternions
{
public:
	void Identity(){ w = 1.0f; x = y = z = 0.0f; }

	//构造执行旋转的四元数
	void setToRotateAboutX(float theta);
	void setToRotateAboutY(float theta);
	void setToRotateAboutZ(float theta);
	void setToRotateAboutAxis(const _Vector3D& axis, float theta);

	//构造执行 物体----惯性  旋转的四元数，方位参数用欧拉角形式给出
	void setToRotateObjectToInertial(const EulerAngles& orientation);
	void setToRotateInertialToObject(const EulerAngles& orientation);

	//叉乘
	Quaternions operator*(const Quaternions& q)const;

	//赋值乘法
	Quaternions& operator*=(const Quaternions& q);

	//将四元数规格化
	void Normalized();

	//提取旋转角和旋转轴
	float getRotationAngle()const;
	_Vector3D getRotationAxis()const;


	float w, x, y, z;
};

//全局单位 四元数
extern const Quaternions kQuaternionIdentity;

//四元数点乘
extern float Dot(const Quaternions& q1, const Quaternions& q2);

//球面线性插值
extern Quaternions slerp(const Quaternions& q1, const Quaternions& q2, float factor);

//四元数共轭
extern Quaternions conjugate(const Quaternions& q);

//四元数幂
extern Quaternions Pow(const Quaternions& q, float exponent);

#endif