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
	//模型视图矩阵
	Matrix4x4 mv = _viewMatrix * _modelMatrix;
	//模型视图投影矩阵
	Matrix4x4 mvp = _projectMatrix * mv;
	//模型空间下的顶点
	_Vector4D modelVert(input.x, input.y, input.z, input.w);
	//世界空间下的顶点
	_Vector4D worldVert = _modelMatrix * modelVert;
	//摄像机空间下的顶点
	_Vector4D viewVert = mv * modelVert;
	//剪裁空间下的顶点
	_Vector4D clipVert = mvp * modelVert;

	//模型空间下的法线
	_Vector4D modelNormal(input.nx, input.ny, input.nz, 0.0);
	//世界空间下的法线
	_Vector4D worldNormal = _modelMatrix * modelNormal;

	//将剪裁空间的坐标值赋值
	output.x = clipVert.GetX();
	output.y = clipVert.GetY();
	output.z = clipVert.GetZ();
	output.w = clipVert.GetW();

	//将世界空间的坐标值赋值
	output.wx = worldVert.GetX();
	output.wy = worldVert.GetY();
	output.wz = worldVert.GetZ();
	output.ww = worldVert.GetW();

	//将摄像机空间的坐标值赋值
	output.vx = viewVert.GetX();
	output.vy = viewVert.GetY();
	output.vz = viewVert.GetZ();
	output.vw = viewVert.GetW();

	//将世界空间的法线坐标值赋值
	output.nx = worldNormal.GetX();
	output.ny = worldNormal.GetY();
	output.nz = worldNormal.GetZ();

	//将纹理坐标值赋值
	output.s = input.s;
	output.t = input.t;
}

void fragmentShader(Fragment input, FragmentOut& output)
{
	_Vector3D worldNormal(input.nx, input.ny, input.nz);
	worldNormal.Normalized();

	_Vector3D worldLightDir(_lightDir.GetX(), _lightDir.GetY(), _lightDir.GetZ());
	worldLightDir.Normalized();

	//将世界空间坐标转换到光源视图投影空间下,为了计算阴影
	_Vector4D shadowVert(input.wx, input.wy, input.wz, input.ww);
	shadowVert = _lightProjectionMatrix * _lightViewMatrix * shadowVert;

	//执行透视除法
	float inverseShadowVertW = 1.0f / shadowVert.GetW();
	shadowVert.SetX(shadowVert.GetX() * inverseShadowVertW);
	shadowVert.SetY(shadowVert.GetY() * inverseShadowVertW);
	shadowVert.SetZ(shadowVert.GetZ() * inverseShadowVertW);

	//影响因子
	float shadowFactor = 0.0f;

	//因为深度贴图的深度在[0,1]范围，如果从深度贴图中去采样，必须将坐标变化到0到1的范围。
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

		//取深度贴图中采样最近的深度
		float depthStore = _depthTexture->texture2D(shadowVert.GetX(), shadowVert.GetY()).GetX();
		/*
		//阴影偏移,防止片元被误认为在表面之下
		//float offset = 0.005f;
		//根据表面朝向光线的角度更改偏移量
		float value = 0.05f * (1.0f - worldLightDir.Dot(worldNormal));
		float offset = max(value, 0.005f);
		//当前片元在光源视角下的深度
		float depthNow = shadowVert.GetZ() + offset;

		//如果当前片元的深度值是否大于从深度贴图中采样得到的最近深度值，是，当前片元就在阴影中
		//shadowFactor = depthNow > depthStore ? 1.0f : 0.0f;
		//这种会因为深度贴图固定的解析度，导致多个片元对应于一个纹理像素，会产生锯齿。
		//通过PCF这种多个不同过滤方式的组合，产生柔和阴影
		//从纹理像素四周对深度贴图采样，然后把结果平均起来

		//取一个纹理像素的宽和高
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

		//平均化
		shadowFactor /= 9.0f;

		//当一个点比光的远平面还要远时，它的投影坐标z的坐标大于1.0
		//解决这个问题，只要投影向量的z坐标大于1.0，我们就把shadowFactor的值强制为0.0
		//意味着，只有在深度贴图范围内被投影的片元坐标才有阴影，而所有超出范围的没有阴影
		if (shadowVert.GetZ() > 1.0f)
		{
			shadowFactor = 0.0f;
		}*/

		//**********注掉上面PCF算法是因为 太卡了!!!**********************//

		float offset = 0.00001f;
		float depthNow = shadowVert.GetZ() + offset;
		if (depthNow > depthStore)
		{
			shadowFactor = 1.0f;
		}

	}

	//世界空间下 光线方向向量与法线的点积，用于后续计算漫反射光照
	float nDotL = worldLightDir.Dot(worldNormal);
	nDotL = max(nDotL, 0.0f);

	//光照：环境光 + 漫反射光
	_Vector4D ambientColor = mul(_ambient, _ambientMat);
	_Vector4D diffuseColor = mul(_diffuse, _diffuseMat) * nDotL;
	_Vector4D lightColor = ambientColor + (1.0f - shadowFactor) * diffuseColor;

	_Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (_currTexture)
	{
		texColor = _currTexture->texture2D(input.s, input.t);
	}

	//最终的片元颜色
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

	//世界空间下 光线方向向量与法线的点积，用于后续计算漫反射光照
	float nDotL = worldLightDir.Dot(worldNormal);
	nDotL = max(nDotL, 0.0f);

	//光照：环境光 + 漫反射光
	_Vector4D lightColor = mul(_ambient, _ambientMat) + mul(_diffuse, _diffuseMat) * nDotL;
	_Vector4D texColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (_currTexture)
	{
		texColor = _currTexture->texture2D(input.s, input.t);
	}
	//最终输出的颜色分量
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
	//归并到[0,1]范围内
	output.r = input.ndcZ * 0.5f + 0.5f;
	output.g = input.ndcZ * 0.5f + 0.5f;
	output.b = input.ndcZ * 0.5f + 0.5f;
	output.a = input.ndcZ * 0.5f + 0.5f;
}

void setAmbientMatFactor(const _Vector4D& mat)
{
	_ambientMat = mat;
}
