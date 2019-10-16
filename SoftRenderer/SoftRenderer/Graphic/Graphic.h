#ifndef  __GRAPHIC__H__
#define  __GRAPHIC__H__

#include "Tools.h"
#include "Face.h"

extern float _eyeX, _eyeY, _eyeZ, _clipNear;
extern Face* _pFace1;
extern Face* _pFace2;
extern bool _bBlendFlag;
extern FrameBuffer* _pFrontBuffer;
extern FrameBuffer* _pBackBuffer;
extern FrameBuffer* _pFrameBuffer1;
extern FrameBuffer* _pFrameBuffer2;
extern DepthBuffer* _pDepthBuffer;
extern unsigned char* _pScreenBits;


struct BlendData
{
	unsigned char srcR;
	unsigned char srcG;
	unsigned char srcB;
	float srcA;
	unsigned char dstR;
	unsigned char dstG;
	unsigned char dstB;
};

//初始化颜色缓冲、深度缓冲
void initFrameBuffer(FrameBuffer** pFrameBuffer,
	int width, int height);
void initDepthBuffer(DepthBuffer** pDepthBuffer,
	int width, int height);
void initDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer,
	int width, int height);
void initDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer, int width, int height);

//清空深度和颜色缓冲
void releaseFrameBuffer(FrameBuffer** pFrameBuffer);
void releaseDepthBuffer(DepthBuffer** pDepthBuffer);
void releaseDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer);
void releaseDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer);

//清除颜色缓冲
void clearScreen(FrameBuffer* pFrameBuffer,
	unsigned char red, unsigned char green, unsigned char blue);
void clearScreenFast(FrameBuffer* pFrameBuffer, unsigned char color);

//清除深度缓冲
void clearDepth(DepthBuffer* pDepthBuffer);

//刷新屏幕
void flush(FrameBuffer* pFrameBuffer);

//双缓冲交换
void swapBuffer();

//转换到屏幕坐标，y轴翻转
void convertToScreen(int height, int& sy);

//面剔除
bool cullFace(Face* pFace, int flag);

//视口变化(到屏幕坐标上)
void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	int& screenX, int& screenY);
void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	float& screenX, float& screenY);

//逆视口变化
void inverseViewPortTransform(int screenX, int screenY,
	float width, float height,
	float& ndcX, float& ndcY);

//光栅化
void rasterize(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	FragmentShader fs, Face* face);

//颜色混合
void blend(BlendData& blendData,
	unsigned char& finalR, unsigned char& finalG, unsigned char& finalB);

//计算边界
void calculateBounds(float srcAX, float scrAY,
	float scrBX, float scrBY,
	float scrCX, float scrCY,
	float startY, float& x1, float& x2);

//绘制三角面
void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Vertex* vertexBuffer,
	int count);
void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Face* pFace);

//设置颜色缓冲中的颜色值
void drawPixel(FrameBuffer* pFrameBuffer,
	int x, int y, unsigned char r, unsigned char g, unsigned char b);

//读取颜色缓冲
void readFrameBuffer(FrameBuffer* pFrameBuffer,
	int x, int y,
	unsigned char& r, unsigned char& g, unsigned char& b);

//写入深度缓冲
void writeDepth(DepthBuffer* pDepthBuffer, int x, int y, float depth);

//读取深度缓冲
float readDepth(DepthBuffer* pDepthBuffer, int x, int y);

//规范化颜色值[0, 255]
void normalizeColor(float r, float g, float b,
	unsigned char& red, unsigned char& green, unsigned char& blue);

//初始化预备面
void initFixFace();

//释放面内存
void releaseFixFace();

//检测三角面三顶点有木有在近剪裁面后的
int checkFace(Face* pFace);

//重新划分三角形
void fixFace(Face* pFace, int fixFlag);

//一个点在近剪裁面后面的情况
void fix1FailFace(VertexOut failVertex, VertexOut succVertex1, VertexOut succVertex2);
//2个点在近剪裁面后面的情况
void fix2FailFace(VertexOut failVertex1, VertexOut failVertex2, VertexOut succVertex);

//插值计算新坐标点
void interpolate2v(float pa, float pb, VertexOut vertex1, VertexOut vertex2, VertexOut& result);
#endif