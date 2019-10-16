#ifndef  __FRAME__H__
#define  __FRAME__H__

#include "Graphic.h"
#include "Key.h"

void draw();
void init();
void release();
void resize(int width, int height);
void move();

//���������
void buildCamera();
//����ͶӰ����
void buildProjectMatrix(int w, int h);

//��ʼ������
void initTextures();
//�ͷ�����
void releaseTextures();
#endif