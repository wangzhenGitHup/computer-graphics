#ifndef  __SAMPLER__H__
#define  __SAMPLER__H__

#include "Tools.h"
#include "SelfMaths.h"
#include "SelfVector4D.h"

class Sampler
{
public:
	Sampler(int sw, int sh);
	~Sampler();
	_Vector4D texture2D(float s, float t);
	void setImgData(int idx, unsigned char ch);
	unsigned char* getImageData(){ return _imgData; }
	int getWidth(){ return _width; }
	int getHeight(){ return _height; }

private:
	int _width;
	int _height;
	unsigned char* _imgData;
};


#endif