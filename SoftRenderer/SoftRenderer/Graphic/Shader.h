#ifndef  __SHADER__H__
#define  __SHADER__H__

#include "Tools.h"
#include "Sampler.h"
#include "SelfMatrix4x4.h"
#include "SelfVector4D.h"

//ģ�;���
extern Matrix4x4 _modelMatrix;
//��ͼ����
extern Matrix4x4 _viewMatrix;
//ͶӰ����
extern Matrix4x4 _projectMatrix;
//��ԴͶӰ����
extern Matrix4x4 _lightProjectionMatrix;
//��Դ��ͼ����
extern Matrix4x4 _lightViewMatrix;
//��Դ��������
extern _Vector4D _lightDir;
//������
extern _Vector4D _ambient;
//�������
extern _Vector4D _diffuse;
//��������
extern _Vector4D _ambientMat;
//���������
extern _Vector4D _diffuseMat;
extern Sampler* _currTexture;
//�������
extern Sampler* _depthTexture;

//����shader����
void vertexShader(Vertex input, VertexOut& output);
//Ƭ��shader����������Ӱ����
void fragmentShader(Fragment input, FragmentOut& output);
//��������Ӱ����
void simpleFragShader(Fragment input, FragmentOut& output);
//�洢��������
void storeVertShader(Vertex input, VertexOut& output);
//�洢Ƭ������
void storeFragShader(Fragment input, FragmentOut& output);
//���ò������������ɫ
void setAmbientMatFactor(const _Vector4D& mat);

#endif