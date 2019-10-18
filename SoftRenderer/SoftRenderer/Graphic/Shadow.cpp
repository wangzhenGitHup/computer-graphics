#include "Shadow.h"
#include "Shader.h"
#include "Utils.h"

FrameBuffer* _pShadowFrame;
DepthBuffer* _pShadowDepth;

static float _shadowSize = 10.0f;

void initShadow(int width, int height)
{
	initDevice(&_pShadowFrame, &_pShadowDepth, width, height);
	_depthTexture = new Sampler(width, height);

	//����һ����Դ�ռ��µ�����ͶӰ����
	_lightProjectionMatrix = ortho(-_shadowSize, _shadowSize,
		-_shadowSize, _shadowSize,
		-_shadowSize, _shadowSize);
	//��Դ�ռ��µ���ͼ����
	_lightViewMatrix = lookAt(_lightDir.GetX(), _lightDir.GetY(), _lightDir.GetZ(),
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
}

void releaseShadow()
{
	delete _depthTexture;
	_depthTexture = nullptr;

	releaseDevice(&_pShadowFrame, &_pShadowDepth);
}

void renderShadowMap(DrawCall renderCall)
{
	float tmpX = _eyeX;
	float tmpY = _eyeY;
	float tmpZ = _eyeZ;
	float tmpNear = _clipNear;
	_eyeX = _lightDir.GetX();// *2.0f;
	_eyeY = _lightDir.GetY();// *2.0f;
	_eyeZ = _lightDir.GetZ();// *2.0f;
	_clipNear = -_shadowSize;

	clearScreenFast(_pShadowFrame, 255);
	clearDepth(_pShadowDepth);

	renderCall();

	writeFrameBufferSampler(_pShadowFrame, _depthTexture);

	_eyeX = tmpX;
	_eyeY = tmpY;
	_eyeZ = tmpZ;
	_clipNear = tmpNear;

}

void writeFrameBufferSampler(FrameBuffer* pFrameBuffer, Sampler* pSampler)
{
	//����Ⱦ�������е����ݸ��Ƹ��������飬��Ҫ������Ӱ��ͼ
	for (int i = 0; i < pFrameBuffer->height; i++)
	{
		for (int j = 0; j < pFrameBuffer->width; j++)
		{
			int idx = (i * pFrameBuffer->width + j) * 3;
			pSampler->setImgData(idx, pFrameBuffer->colorBuffer[idx]);
			pSampler->setImgData(idx + 1, pFrameBuffer->colorBuffer[idx + 1]);
			pSampler->setImgData(idx + 2, pFrameBuffer->colorBuffer[idx + 2]);
		}
	}
}
