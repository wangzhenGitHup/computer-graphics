#include "BmpLoader.h"
#include <stdio.h>

BmpLoader::BmpLoader()
{
	_header = new unsigned char[54];
}

BmpLoader::~BmpLoader()
{
	delete[] _header;
	delete[] _data;
}

int BmpLoader::getWidth()
{
	return _width;
}

int BmpLoader::getHeight()
{
	return _height;
}

bool BmpLoader::loadBitmap(const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb");
	if (!pFile)
	{
		printf("Image %s could not be opened\n", fileName);
		return false;
	}

	//文件头并非54字节，读取失败
	if (fread(_header, 1, 54, pFile) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	//文件头开头并非BM，读取失败
	if (_header[0] != 'B' || _header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	_dataPos = *(int*)&(_header[0X0A]); //读取位置，位置在文件头0X0A处
	_imageSize = *(int*)&(_header[0X22]); //图片内容大小数据，位置在文件头0X22处
	_width = *(int*)&(_header[0X12]); //图片宽度数据，位置在文件头0X12处
	_height = *(int*)&(_header[0X16]); //图片高度数据，位置在文件头0X16处

	if (_imageSize == 0)
	{
		_imageSize = _width * _height * 3; //图片内容数据 == 总像素x3
	}

	if (_dataPos == 0)
	{
		_dataPos = 54; //文件头读完，位置在54字节处
	}

	_data = new unsigned char[_imageSize]; //data放像素信息
	fread(_data, 1, _imageSize, pFile); //读取像素
	fclose(pFile);

	for (int i = 0; i < (int)_imageSize; i += 3)
	{
		swapColor(_data[i], _data[i + 2]);
	}

	return true;
}
