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

//��ʼ����ɫ���塢��Ȼ���
void initFrameBuffer(FrameBuffer** pFrameBuffer,
	int width, int height);
void initDepthBuffer(DepthBuffer** pDepthBuffer,
	int width, int height);
void initDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer,
	int width, int height);
void initDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer, int width, int height);

//�����Ⱥ���ɫ����
void releaseFrameBuffer(FrameBuffer** pFrameBuffer);
void releaseDepthBuffer(DepthBuffer** pDepthBuffer);
void releaseDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer);
void releaseDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer);

//�����ɫ����
void clearScreen(FrameBuffer* pFrameBuffer,
	unsigned char red, unsigned char green, unsigned char blue);
void clearScreenFast(FrameBuffer* pFrameBuffer, unsigned char color);

//�����Ȼ���
void clearDepth(DepthBuffer* pDepthBuffer);

//ˢ����Ļ
void flush(FrameBuffer* pFrameBuffer);

//˫���彻��
void swapBuffer();

//ת������Ļ���꣬y�ᷭת
void convertToScreen(int height, int& sy);

//���޳�
bool cullFace(Face* pFace, int flag);

//�ӿڱ仯(����Ļ������)
void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	int& screenX, int& screenY);
void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	float& screenX, float& screenY);

//���ӿڱ仯
void inverseViewPortTransform(int screenX, int screenY,
	float width, float height,
	float& ndcX, float& ndcY);

//��դ��
void rasterize(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	FragmentShader fs, Face* face);

//��ɫ���
void blend(BlendData& blendData,
	unsigned char& finalR, unsigned char& finalG, unsigned char& finalB);

//����߽�
void calculateBounds(float srcAX, float scrAY,
	float scrBX, float scrBY,
	float scrCX, float scrCY,
	float startY, float& x1, float& x2);

//����������
void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Vertex* vertexBuffer,
	int count);
void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Face* pFace);

//������ɫ�����е���ɫֵ
void drawPixel(FrameBuffer* pFrameBuffer,
	int x, int y, unsigned char r, unsigned char g, unsigned char b);

//��ȡ��ɫ����
void readFrameBuffer(FrameBuffer* pFrameBuffer,
	int x, int y,
	unsigned char& r, unsigned char& g, unsigned char& b);

//д����Ȼ���
void writeDepth(DepthBuffer* pDepthBuffer, int x, int y, float depth);

//��ȡ��Ȼ���
float readDepth(DepthBuffer* pDepthBuffer, int x, int y);

//�淶����ɫֵ[0, 255]
void normalizeColor(float r, float g, float b,
	unsigned char& red, unsigned char& green, unsigned char& blue);

//��ʼ��Ԥ����
void initFixFace();

//�ͷ����ڴ�
void releaseFixFace();

//�����������������ľ���ڽ���������
int checkFace(Face* pFace);

//���»���������
void fixFace(Face* pFace, int fixFlag);

//һ�����ڽ��������������
void fix1FailFace(VertexOut failVertex, VertexOut succVertex1, VertexOut succVertex2);
//2�����ڽ��������������
void fix2FailFace(VertexOut failVertex1, VertexOut failVertex2, VertexOut succVertex);

//��ֵ�����������
void interpolate2v(float pa, float pb, VertexOut vertex1, VertexOut vertex2, VertexOut& result);
#endif