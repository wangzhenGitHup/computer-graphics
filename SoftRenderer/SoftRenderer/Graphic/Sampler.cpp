#include "Sampler.h"

Sampler::Sampler(int sw, int sh)
{
	_width = sw;
	_height = sh;
	//纹理的宽高，一个纹理包含rgb3个分量，所以开辟这么大的一块空间用于保存纹理数据
	_imgData = new unsigned char[_width * _height * 3];
	memset(_imgData, 0, _width * _height * 3 * sizeof(unsigned char));
}

Sampler::~Sampler()
{
	delete[] _imgData;
	_imgData = nullptr;
}

_Vector4D Sampler::texture2D(float s, float t)
{
	_Vector4D color(1.0f, 1.0f, 1.0f, 1.0f);
	//纹理坐标的获取
	float u = (float)(_width - 1) * s;
	//屏幕坐标和纹理坐标y轴相反
	float v = (float)(_height - 1) * (1.0f - t);

	// 线性采样，过滤掉了小数点部分
	int iu = (int)u;
	int iv = (int)v;
	//对周围纹理采样
	int uNext = (iu + 1) <= (_width - 1) ? iu + 1 : iu;
	int vNext = (iv + 1) <= (_height - 1) ? iv + 1 : iv;

	//上面线性采样损失的小数点部分
	float uNextPer = u - iu;
	float vNextPer = v - iv;
	float uPer = 1.0f - uNextPer;
	float vPer = 1.0f - vNextPer;

	//根据纹理坐标取得纹理数据数组的下标
	int imgIdx = 3 * (iv * _width + iu);
	//规范到[0.0f, 1.0f]内
	float x = (float)(_imgData[imgIdx] * INV_SCALE);
	float y = (float)(_imgData[imgIdx + 1] * INV_SCALE);
	float z = (float)(_imgData[imgIdx + 2] * INV_SCALE);

	color.Set(x, y, z, 1.0f);

	//周围纹理坐标所在纹理数据数组的下标值
	int imgIdxNextU = 3 * (iv * _width + uNext);
	int imgIdxNextV = 3 * (vNext * _width + iu);
	int imgIdxNextUV = 3 * (vNext * _width + uNext);

	_Vector4D colorNextU(1.0f, 1.0f, 1.0f, 1.0f);
	_Vector4D colorNextV(1.0f, 1.0f, 1.0f, 1.0f);
	_Vector4D colorNextUV(1.0f, 1.0f, 1.0f, 1.0f);

	colorNextU.SetX((float)(_imgData[imgIdxNextU] * INV_SCALE));
	colorNextU.SetY((float)(_imgData[imgIdxNextU + 1] * INV_SCALE));
	colorNextU.SetZ((float)(_imgData[imgIdxNextU + 2] * INV_SCALE));

	colorNextV.SetX((float)(_imgData[imgIdxNextV] * INV_SCALE));
	colorNextV.SetY((float)(_imgData[imgIdxNextV + 1] * INV_SCALE));
	colorNextV.SetZ((float)(_imgData[imgIdxNextV + 2] * INV_SCALE));

	colorNextUV.SetX((float)(_imgData[imgIdxNextUV] * INV_SCALE));
	colorNextUV.SetY((float)(_imgData[imgIdxNextUV + 1] * INV_SCALE));
	colorNextUV.SetZ((float)(_imgData[imgIdxNextUV + 2] * INV_SCALE));

	//按小数部分的值进行比例计算混合，得到最终采样的纹理颜色值
	float tmpX = color.GetX()*uPer * vPer + 
		colorNextU.GetX() * uNextPer * vPer + 
		colorNextV.GetX() * uPer * vNextPer + 
		colorNextUV.GetX() * uNextPer * vNextPer;

	float tmpY = color.GetY() * uPer * vPer + 
		colorNextU.GetY() * uNextPer*vPer + 
		colorNextV.GetY() * uPer * vNextPer + 
		colorNextUV.GetY() * uNextPer * vNextPer;

	float tmpZ = color.GetZ() * uPer * vPer + 
		colorNextU.GetZ() * uNextPer * vPer + 
		colorNextV.GetZ() * uPer * vNextPer + 
		colorNextUV.GetZ()*uNextPer * vNextPer;

	color.Set(tmpX, tmpY, tmpZ, 1.0);
	return color;
}

void Sampler::setImgData(int idx, unsigned char ch)
{
	_imgData[idx] = ch;
}