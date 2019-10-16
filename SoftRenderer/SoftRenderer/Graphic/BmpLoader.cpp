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

	//�ļ�ͷ����54�ֽڣ���ȡʧ��
	if (fread(_header, 1, 54, pFile) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	//�ļ�ͷ��ͷ����BM����ȡʧ��
	if (_header[0] != 'B' || _header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	_dataPos = *(int*)&(_header[0X0A]); //��ȡλ�ã�λ�����ļ�ͷ0X0A��
	_imageSize = *(int*)&(_header[0X22]); //ͼƬ���ݴ�С���ݣ�λ�����ļ�ͷ0X22��
	_width = *(int*)&(_header[0X12]); //ͼƬ������ݣ�λ�����ļ�ͷ0X12��
	_height = *(int*)&(_header[0X16]); //ͼƬ�߶����ݣ�λ�����ļ�ͷ0X16��

	if (_imageSize == 0)
	{
		_imageSize = _width * _height * 3; //ͼƬ�������� == ������x3
	}

	if (_dataPos == 0)
	{
		_dataPos = 54; //�ļ�ͷ���꣬λ����54�ֽڴ�
	}

	_data = new unsigned char[_imageSize]; //data��������Ϣ
	fread(_data, 1, _imageSize, pFile); //��ȡ����
	fclose(pFile);

	for (int i = 0; i < (int)_imageSize; i += 3)
	{
		swapColor(_data[i], _data[i + 2]);
	}

	return true;
}
