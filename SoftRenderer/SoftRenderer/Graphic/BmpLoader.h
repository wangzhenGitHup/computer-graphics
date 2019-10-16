#ifndef  __BMPLOADER__H__
#define  __BMPLOADER__H__

#define BLUIE 0 
#define GREEN 1
#define RED   2

#define swapColor(a, b) {\
	(a) ^= (b); \
	(b) ^= (a); \
	(a) ^= (b); \
}

class BmpLoader
{
public:
	BmpLoader();
	~BmpLoader();
	int getWidth();
	int getHeight();
	unsigned char* getData(){ return _data; }
	bool loadBitmap(const char* fileName);

private:
	unsigned char* _header; //�ļ�ͷ
	unsigned int _dataPos; //��ȡλ��
	unsigned int _imageSize; //ͼƬ���ݴ�С
	unsigned char* _data; //ͼƬ����rgb
	unsigned int _width, _height; //ͼƬ���
};

#endif