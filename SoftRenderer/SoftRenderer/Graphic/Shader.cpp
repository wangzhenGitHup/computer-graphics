#include "Shader.h"
#include "SelfVector3D.h"
#include "SelfVector2D.h"
#include "SelfVector4D.h"
#include "SelfMaths.h"
#include "Utils.h"
#include "Tools.h"

Matrix4x4 _modelMatrix;
Matrix4x4 _viewMatrix;
Matrix4x4 _projectMatrix;
Matrix4x4 _lightProjectionMatrix;
Matrix4x4 _lightViewMatrix;
_Vector4D _lightDir;
_Vector4D _ambient;
_Vector4D _diffuse;
_Vector4D _ambientMat;
_Vector4D _diffuseMat;
Sampler* _currTexture = nullptr;
Sampler* _depthTexture = nullptr;

void vertexShader(Vertex input, VertexOut& output)
{
	//ģ����ͼ����
	Matrix4x4 mv = _viewMatrix * _modelMatrix;
	//ģ����ͼͶӰ����
	Matrix4x4 mvp = _projectMatrix * mv;
	//ģ�Ϳռ��µĶ���
	_Vector4D modelVert(input.x, input.y, input.z, input.w);
	//����ռ��µĶ���
	_Vector4D worldVert = _modelMatrix * modelVert;
	//������ռ��µĶ���
	_Vector4D viewVert = mv * modelVert;
	//���ÿռ��µĶ���
	_Vector4D clipVert = mvp * modelVert;

	//ģ�Ϳռ��µķ���
	_Vector4D modelNormal(input.nx, input.ny, input.nz, 0.0);
	//����ռ��µķ���
	_Vector4D worldNormal = _modelMatrix * modelNormal;

	//�����ÿռ������ֵ��ֵ
	output.x = clipVert.GetX();
	output.y = clipVert.GetY();
	output.z = clipVert.GetZ();
	output.w = clipVert.GetW();

	//������ռ������ֵ��ֵ
	output.wx = worldVert.GetX();
	output.wy = worldVert.GetY();
	output.wz = worldVert.GetZ();
	output.ww = worldVert.GetW();

	//��������ռ������ֵ��ֵ
	output.vx = viewVert.GetX();
	output.vy = viewVert.GetY();
	output.vz = viewVert.GetZ();
	output.vw = viewVert.GetW();

	//������ռ�ķ�������ֵ��ֵ
	output.nx = worldNormal.GetX();
	output.ny = worldNormal.GetY();
	output.nz = worldNormal.GetZ();

	//����������ֵ��ֵ
	output.s = input.s;
	output.t = input.t;
}

void fragmentShader(Fragment input, FragmentOut& output)
{
	_Vector3D worldNormal(input.nx, input.ny, input.nz);
	worldNormal.Normalized();

	_Vector3D worldLightDir(_lightDir.GetX(), _lightDir.GetY(), _lightDir.GetZ());
	worldLightDir.Normalized();

	//������ռ�����ת������Դ��ͼͶӰ�ռ���,Ϊ�˼�����Ӱ
	_Vector4D shadowVert(input.wx, input.wy, input.wz, input.ww);
	shadowVert = _lightProjectionMatrix * _lightViewMatrix * shadowVert;

	//ִ��͸�ӳ���
	float inverseShadowVertW = 1.0f / shadowVert.GetW();
	shadowVert.SetX(shadowVert.GetX() * inverseShadowVertW);
	shadowVert.SetY(shadowVert.GetY() * inverseShadowVertW);
	shadowVert.SetZ(shadowVert.GetZ() * inverseShadowVertW);

	//Ӱ������
	float shadowFactor = 0.0f;

	//��Ϊ�����ͼ�������[0,1]��Χ������������ͼ��ȥ���������뽫����仯��0��1�ķ�Χ��
	//projCoords = projCoords * 0.5 + 0.5
	if ((shadowVert.GetX() < 1.0f || FLT_EQUAL(shadowVert.GetX(), 1.0f)) &&
		(shadowVert.GetX() > -1.0f || FLT_EQUAL(shadowVert.GetX(), -1.0f)) && 
		(shadowVert.GetY() < 1.0f || FLT_EQUAL(shadowVert.GetY(), 1.0f)) &&
		(shadowVert.GetY() > -1.0f || FLT_EQUAL(shadowVert.GetY(), -1.0f)) &&
		(shadowVert.GetZ() < 1.0f || FLT_EQUAL(shadowVert.GetZ(), 1.0f)) &&
		(shadowVert.GetZ() > -1.0f || FLT_EQUAL(shadowVert.GetZ(), -1.0f)))
	{
		float tmpX = 0.5f * (shadowVert.GetX() + 1.0f);
		shadowVert.SetX(tmpX);

		float tmpY = 0.5f * (shadowVert.GetY() + 1.0f);
		shadowVert.SetY(tmpY);

		float tmpZ = 0.5f * (shadowVert.GetZ() + 1.0f);
		shadowVert.SetZ(tmpZ);

		//ȡ�����ͼ�в�����������
		float depthStore = _depthTexture->texture2D(shadowVert.GetX(), shadowVert.GetY()).GetX();
		/*
		//��Ӱƫ��,��ֹƬԪ������Ϊ�ڱ���֮��
		//float offset = 0.005f;
		//���ݱ��泯����ߵĽǶȸ���ƫ����
		float value = 0.05f * (1.0f - worldLightDir.Dot(worldNormal));
		float offset = max(value, 0.005f);
		//��ǰƬԪ�ڹ�Դ�ӽ��µ����
		float depthNow = shadowVert.GetZ() + offset;

		//�����ǰƬԪ�����ֵ�Ƿ���ڴ������ͼ�в����õ���������ֵ���ǣ���ǰƬԪ������Ӱ��
		//shadowFactor = depthNow > depthStore ? 1.0f : 0.0f;
		//���ֻ���Ϊ�����ͼ�̶��Ľ����ȣ����¶��ƬԪ��Ӧ��һ���������أ��������ݡ�
		//ͨ��PCF���ֶ����ͬ���˷�ʽ����ϣ����������Ӱ
		//�������������ܶ������ͼ������Ȼ��ѽ��ƽ������

		//ȡһ���������صĿ�͸�
		float singleTexW = 1.0f / (float)_depthTexture->getWidth();
		float singleTexH = 1.0f / (float)_depthTexture->getHeight();
		_Vector2D texelSizeVec(singleTexW, singleTexH);
		_Vector2D shadowVertXY(shadowVert.GetX(), shadowVert.GetY());

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				_Vector2D tmpVec((float)i, (float)j);
				_Vector2D texCoord = shadowVertXY + tmpVec * texelSizeVec;
				float pcfDepth = _depthTexture->texture2D(texCoord.GetX(), texCoord.GetY()).GetX();
				shadowFactor += depthNow - offset > pcfDepth ? 1.0f : 0.0f;
			}
		}

		//ƽ����
		shadowFactor /= 9.0f;

		//��һ����ȹ��Զƽ�滹ҪԶʱ������ͶӰ����z���������1.0
		//���������⣬ֻҪͶӰ������z�������1.0�����ǾͰ�shadowFactor��ֵǿ��Ϊ0.0
		//��ζ�ţ�ֻ���������ͼ��Χ�ڱ�ͶӰ��ƬԪ���������Ӱ�������г�����Χ��û����Ӱ
		if (shadowVert.GetZ() > 1.0f)
		{
			shadowFactor = 0.0f;
		}*/

		//**********ע������PCF�㷨����Ϊ ̫����!!!**********************//

		float offset = 0.00001f;
		float depthNow = shadowVert.GetZ() + offset;
		if (depthNow > depthStore)
		{
			shadowFactor = 1.0f;
		}

	}

	//����ռ��� ���߷��������뷨�ߵĵ�������ں����������������
	float nDotL = worldLightDir.Dot(worldNormal);
	nDotL = max(nDotL, 0.0f);

	//���գ������� + �������
	_Vector4D ambientColor = mul(_ambient, _ambientMat);
	_Vector4D diffuseColor = mul(_diffuse, _diffuseMat) * nDotL;
	_Vector4D lightColor = ambientColor + (1.0f - shadowFactor) * diffuseColor;

	_Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (_currTexture)
	{
		texColor = _currTexture->texture2D(input.s, input.t);
	}

	//���յ�ƬԪ��ɫ
	output.r = texColor.GetX() * lightColor.GetX();
	output.g = texColor.GetY() * lightColor.GetY();
	output.b = texColor.GetZ() * lightColor.GetZ();
	output.a = texColor.GetW() * lightColor.GetW();
}

void simpleFragShader(Fragment input, FragmentOut& output)
{
	_Vector3D worldNormal(input.nx, input.ny, input.nz);
	worldNormal.Normalized();

	_Vector3D worldLightDir(_lightDir.GetX(), _lightDir.GetY(), _lightDir.GetZ());
	worldLightDir.Normalized();

	//����ռ��� ���߷��������뷨�ߵĵ�������ں����������������
	float nDotL = worldLightDir.Dot(worldNormal);
	nDotL = max(nDotL, 0.0f);

	//���գ������� + �������
	_Vector4D lightColor = mul(_ambient, _ambientMat) + mul(_diffuse, _diffuseMat) * nDotL;
	_Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (_currTexture)
	{
		texColor = _currTexture->texture2D(input.s, input.t);
	}
	//�����������ɫ����
	output.r = texColor.GetX() * lightColor.GetX();
	output.g = texColor.GetY() * lightColor.GetY();
	output.b = texColor.GetZ() * lightColor.GetZ();
	output.a = texColor.GetW() * lightColor.GetW();
}

void storeVertShader(Vertex input, VertexOut& output)
{
	Matrix4x4 mv = _lightViewMatrix * _modelMatrix;
	Matrix4x4 mvp = _lightProjectionMatrix * mv;
	_Vector4D modelVert(input.x, input.y, input.z, input.w);
	_Vector4D worldVert = _modelMatrix * modelVert;
	_Vector4D viewVert = mv * modelVert;
	_Vector4D clipVert = mvp * modelVert;

	_Vector4D modelNormal(input.nx, input.ny, input.nz, 0.0f);
	_Vector4D worldNormal = _modelMatrix * modelNormal;

	output.x = clipVert.GetX();
	output.y = clipVert.GetY();
	output.z = clipVert.GetZ();
	output.w = clipVert.GetW();

	output.wx = worldVert.GetX();
	output.wy = worldVert.GetY();
	output.wz = worldVert.GetZ();
	output.ww = worldVert.GetW();

	output.vx = viewVert.GetX();
	output.vy = viewVert.GetY();
	output.vz = viewVert.GetZ();
	output.vw = viewVert.GetW();

	output.nx = worldNormal.GetX();
	output.ny = worldNormal.GetY();
	output.nz = worldNormal.GetZ();
}

void storeFragShader(Fragment input, FragmentOut& output)
{
	//�鲢��[0,1]��Χ��
	output.r = input.ndcZ * 0.5f + 0.5f;
	output.g = input.ndcZ * 0.5f + 0.5f;
	output.b = input.ndcZ * 0.5f + 0.5f;
	output.a = input.ndcZ * 0.5f + 0.5f;
}

void setAmbientMatFactor(const _Vector4D& mat)
{
	_ambientMat = mat;
}
