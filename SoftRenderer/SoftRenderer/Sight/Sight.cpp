#include "Sight.h"

Sight::Sight(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_rotate_x = _rotate_y = _rotate_z = 0.0f;
}

void Sight::turnX(int code)
{
	switch (code)
	{
	case LEFT:
		_rotate_x -= D_ROTATION;
		break;

	case RIGHT:
		_rotate_x += D_ROTATION;
	}

	if (_rotate_x > 360.0f)
	{
		_rotate_x -= 360.0f;
	}
	else if (_rotate_x < 0.0f)
	{
		_rotate_x += 360.0f;
	}
}

void Sight::turnY(int code)
{
	switch (code)
	{
	case UP:
		_rotate_y -= D_ROTATION;
		break;

	case DOWN:
		_rotate_y += D_ROTATION;
		break;
	}

	if (_rotate_y > 360.0f)
	{
		_rotate_y -= 360.0f;
	}
	else if (_rotate_y < 0.0f)
	{
		_rotate_y += 360.0f;
	}
}

void Sight::moveSight(int dist, float spd)
{
	float radinsX_Z = ATR(_rotate_x);
	float radinsY_Z = ATR(_rotate_y);
	float dx = spd * cos(radinsY_Z) * sin(radinsX_Z);
	float dy = spd * sin(radinsY_Z);
	float dz = spd * cos(radinsY_Z) * cos(radinsX_Z);

	switch (dist)
	{
	case DOWN:
		_y += spd;
		_h -= spd;
		break;

	case UP:
		_y -= spd;
		_h += spd;
		break;

	case RIGHT:
		_x -= spd * cos(radinsX_Z);
		_z -= spd * sin(radinsX_Z);
		break;

	case LEFT:
		_x += spd * cos(radinsX_Z);
		_z += spd * sin(radinsX_Z);
		break;

	case MFAR:
		_x += dx;
		_y -= dy;
		_z -= dz;
		break;

	case MNEAR:
		_x -= dx;
		_y += dy;
		_z += dz;
		break;
	}
}

float ATR(float angle)
{
	return (float)(angle * A2R);
}

float RTA(float radins)
{
	return (float)(radins * R2A);
}
