#ifndef  __SIGHT__H__
#define  __SIGHT__H__

#include "Tools.h"

class Sight
{
public:
	Sight(float x, float y, float z);
	void turnX(int code);
	void turnY(int code);
	void moveSight(int dist, float spd);

public:
	float _x;
	float _y;
	float _z;
	float _h;
	float _rotate_x;
	float _rotate_y;
	float _rotate_z;
};

//�Ƕ�ת����
float ATR(float angle);
//����ת�Ƕ�
float RTA(float radins);
 
#endif