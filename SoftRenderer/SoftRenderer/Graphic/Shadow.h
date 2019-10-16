#ifndef  __SHADOW__H__
#define  __SHADOW__H__

#include "Graphic.h"
#include "Sampler.h"
#include "Tools.h"

extern FrameBuffer* _pShadowFrame;
extern DepthBuffer* _pShadowDepth;

void initShadow(int width, int height);
void releaseShadow();

void renderShadowMap(DrawCall renderCall);
//将颜色缓冲写进纹理中
void writeFrameBufferSampler(FrameBuffer* pFrameBuffer, Sampler* pSampler);
#endif