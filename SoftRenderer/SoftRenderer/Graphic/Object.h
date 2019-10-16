#ifndef  __OBJECT__H__
#define  __OBJECT__H__

#include "Texture.h"
#include "Shader.h"
#include "Shadow.h"
#include "Cube.h"
#include "Square.h"

extern Texture* _texCube;
extern Texture* _texFloor;
extern Cube* _cube;
extern Square* _square;

//��ʼ����������
void initLightingData();
//��ʼ�������嶥������
void initCube();
//��ʼ��ƽ�涥������
void initSquare();
//�ͷ��������ڴ�
void releaseCube();
//�ͷ�ƽ���ڴ�
void releaseSquare();
//��Ⱦ��������ͼ��������
void renderCube(bool bWithShadow = true);
//��Ⱦ��ͨ������
void renderSimpleCube();
//��Ⱦ��������Ӱ
void renderCubeShadow();
//��Ⱦƽ��
void renderSquare(bool bWithShadow = true);
//������������Ⱦ����
void setRenderCubeData(float angle, float fScale, const _Vector3D& vec);

#endif