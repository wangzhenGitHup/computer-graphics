#include "Object.h"

Texture* _texCube;
Texture* _texFloor;
Cube* _cube;
Square* _square;

static float s_angle_cube = 0.0f;
static float s_scale_cube = 1.0f;
static _Vector3D s_vec_cube;

void initLightingData()
{
	//光源方向
	_lightDir.Set(-2.0f, 2.0f, -1.0f, 0.0f);

	//环境光
	_ambient.Set(0.72f, 0.72f, 0.72f, 1.0f);


	//环境材质
	_ambientMat.Set(0.72f, 0.72f, 0.72f, 1.0f);

	//漫反射光
	_diffuse.Set(0.7f, 0.7f, 0.7f, 1.0f);


	//漫反射材质
	_diffuseMat.Set(0.7f, 0.7f, 0.7f, 1.0f);
}

void initCube()
{
	_cube = new Cube();
}

void releaseCube()
{
	delete _cube;
	_cube = nullptr;
}

void renderCube(bool bWithShadow)
{
	//摆放立方体
	_modelMatrix.LoadIdentity();
	Matrix4x4 rotMat = rotateY(s_angle_cube);                  //旋转矩阵
	Matrix4x4 transMat = translate(s_vec_cube.GetX(), 
		s_vec_cube.GetY(), s_vec_cube.GetZ());				  //移动矩阵
	Matrix4x4 scaleMat = scale(s_scale_cube);                //缩放矩阵

	_modelMatrix = transMat * rotMat * scaleMat;
	if (_texCube)
	{
		_currTexture = _texCube->getSampler();
	}
	_cube->render(_pFrontBuffer, _pDepthBuffer, vertexShader, bWithShadow ? fragmentShader : simpleFragShader, CULL_BACK);
}

void renderCubeShadow()
{
	//立方体阴影处理
	_modelMatrix.LoadIdentity();
	Matrix4x4 rotMat = rotateY(s_angle_cube);
	Matrix4x4 transMat = translate(s_vec_cube.GetX(), s_vec_cube.GetY(), s_vec_cube.GetZ());
	Matrix4x4 scaleMat = scale(s_scale_cube);

	_modelMatrix = transMat * rotMat * scaleMat;
	if (_texCube)
	{
		_currTexture = _texCube->getSampler();
	}
	_cube->render(_pShadowFrame, _pShadowDepth, storeVertShader, storeFragShader, CULL_FRONT);
}

void renderSimpleCube()
{
	//摆放立方体
	_modelMatrix.LoadIdentity();
	Matrix4x4 rotMat = rotateY(s_angle_cube);                  //旋转矩阵
	Matrix4x4 transMat = translate(s_vec_cube.GetX(),
		s_vec_cube.GetY(), s_vec_cube.GetZ());				  //移动矩阵
	Matrix4x4 scaleMat = scale(s_scale_cube);                //缩放矩阵
	_currTexture = nullptr;
	_modelMatrix = transMat * rotMat * scaleMat;
	_cube->render(_pFrontBuffer, _pDepthBuffer, vertexShader, simpleFragShader, CULL_BACK);
}

void setRenderCubeData(float angle, float fScale, const _Vector3D& vec)
{
	s_angle_cube = angle;
	s_scale_cube = fScale;
	s_vec_cube = vec;
}

void initSquare()
{
	_square = new Square();
}

void releaseSquare()
{
	delete _square;
	_square = nullptr;
}

void renderSquare(bool bWithShadow)
{
	//摆放地面
	_modelMatrix.LoadIdentity();
	Matrix4x4 transMat = translate(0.0f, 0.0f, 0.0f);
	Matrix4x4 scaleMat = scale(50.0f);
	_modelMatrix = transMat * scaleMat;
	if (_texFloor)
	{
		_currTexture = _texFloor->getSampler();
	}
	_square->render(_pFrontBuffer, _pDepthBuffer, vertexShader, !bWithShadow ? simpleFragShader : fragmentShader, CULL_BACK);
}