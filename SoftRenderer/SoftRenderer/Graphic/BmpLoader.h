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
	unsigned char* _header; //文件头
	unsigned int _dataPos; //读取位置
	unsigned int _imageSize; //图片内容大小
	unsigned char* _data; //图片内容rgb
	unsigned int _width, _height; //图片宽高
};

#endif