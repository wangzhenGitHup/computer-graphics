#ifndef  __SHADER__H__
#define  __SHADER__H__

#include "Tools.h"
#include "Sampler.h"
#include "SelfMatrix4x4.h"
#include "SelfVector4D.h"

//模型矩阵
extern Matrix4x4 _modelMatrix;
//视图矩阵
extern Matrix4x4 _viewMatrix;
//投影矩阵
extern Matrix4x4 _projectMatrix;
//光源投影矩阵
extern Matrix4x4 _lightProjectionMatrix;
//光源视图矩阵
extern Matrix4x4 _lightViewMatrix;
//光源方向向量
extern _Vector4D _lightDir;
//环境光
extern _Vector4D _ambient;
//漫反射光
extern _Vector4D _diffuse;
//环境材质
extern _Vector4D _ambientMat;
//漫反射材质
extern _Vector4D _diffuseMat;
extern Sampler* _currTexture;
//深度纹理
extern Sampler* _depthTexture;

//顶点shader函数
void vertexShader(Vertex input, VertexOut& output);
//片段shader函数【含阴影处理】
void fragmentShader(Fragment input, FragmentOut& output);
//【不含阴影处理】
void simpleFragShader(Fragment input, FragmentOut& output);
//存储顶点数据
void storeVertShader(Vertex input, VertexOut& output);
//存储片段数据
void storeFragShader(Fragment input, FragmentOut& output);
//设置材质自身光照颜色
void setAmbientMatFactor(const _Vector4D& mat);

#endif