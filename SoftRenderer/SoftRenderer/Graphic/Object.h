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

//初始化光照数据
void initLightingData();
//初始化立方体顶点数据
void initCube();
//初始化平面顶点数据
void initSquare();
//释放立方体内存
void releaseCube();
//释放平面内存
void releaseSquare();
//渲染有纹理贴图的立方体
void renderCube(bool bWithShadow = true);
//渲染普通立方体
void renderSimpleCube();
//渲染立方体阴影
void renderCubeShadow();
//渲染平面
void renderSquare(bool bWithShadow = true);
//设置立方体渲染数据
void setRenderCubeData(float angle, float fScale, const _Vector3D& vec);

#endif