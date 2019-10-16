#ifndef  __FRAME__H__
#define  __FRAME__H__

#include "Graphic.h"
#include "Key.h"

void draw();
void init();
void release();
void resize(int width, int height);
void move();

//构建摄像机
void buildCamera();
//构建投影矩阵
void buildProjectMatrix(int w, int h);

//初始化纹理
void initTextures();
//释放纹理
void releaseTextures();
#endif