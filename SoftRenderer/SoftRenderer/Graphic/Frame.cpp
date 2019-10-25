#include "Frame.h"
#include "Sight.h"
#include "SelfMatrix4x4.h"
#include "Shader.h"
#include "Shadow.h"
#include "Object.h"

Sight* _sight = nullptr;

void draw()
{
	//清除颜色缓冲
	clearScreen(_pFrontBuffer, 51, 76, 76);
	//清除深度缓冲
	clearDepth(_pDepthBuffer);
	//构建摄像机
	buildCamera();

	//模型单位矩阵构建
	_modelMatrix.LoadIdentity();

	//设置渲染立方体的数据
	setRenderCubeData(30.0f, 1.0f, _Vector3D(0.0f, 1.0f, 0.0f));
	setAmbientMatFactor(_Vector4D(1.0f, 1.0f, 1.0f, 1.0f));
	//渲染阴影贴图
	renderShadowMap(renderCubeShadow);
	//渲染立方体
	renderCube();

	//渲染平面
	setAmbientMatFactor(_Vector4D(1.0f, 1.0f, 1.0f, 1.0f));
	renderSquare(true);

	//再渲染一个普通的立方体
	setRenderCubeData(30.0f, 1.0f, _Vector3D(-4.0f, 2.0f, 0.0f));
	//设置材质
	setAmbientMatFactor(_Vector4D(1.0f, 1.0f, 0.0f, 1.0f));
	renderSimpleCube();


	//交换前后缓存
	swapBuffer();
}

void init()
{
	initFixFace();
	initLightingData();
	initTextures();
	initShadow(256, 256);
	initCube();
	initSquare();

	_eyeX = -1.0f;
	_eyeY = 1.0f;
	_eyeZ = -6.0f;
	_sight = new Sight(-_eyeX, -_eyeY, -_eyeZ);
	_sight->_rotate_x = 180.0f;
	_sight->_rotate_y = 0.0f;

	initKeys();
}

void release()
{
	releaseKeys();
	delete _sight;
	_sight = nullptr;

	releaseSquare();
	releaseCube();
	releaseShadow();
	releaseTextures();
	releaseFixFace();
	releaseDevice2Buffer(&_pFrameBuffer1, &_pFrameBuffer2, &_pDepthBuffer);
}

void resize(int width, int height)
{
	releaseDevice2Buffer(&_pFrameBuffer1, &_pFrameBuffer2, &_pDepthBuffer);
	initDevice2Buffer(&_pFrameBuffer1, &_pFrameBuffer2, &_pDepthBuffer, width, height);
	buildProjectMatrix(width, height);
}

void move()
{
	if (_sight)
	{
		if (bMove[0])
		{
			_sight->moveSight(MNEAR, D_DISTANCE);
		}

		if (bMove[1])
		{
			_sight->moveSight(MFAR, D_DISTANCE);
		}

		if (bMove[2])
		{
			_sight->moveSight(LEFT, D_DISTANCE);
		}

		if (bMove[3])
		{
			_sight->moveSight(RIGHT, D_DISTANCE);
		}

		if (bMove[4])
		{
			_sight->moveSight(UP, D_DISTANCE);
		}

		if (bMove[5])
		{
			_sight->moveSight(DOWN, D_DISTANCE);
		}

		if (bTurn[0])
		{
			_sight->turnY(UP);
		}

		if (bTurn[1])
		{
			_sight->turnY(DOWN);
		}

		if (bTurn[2])
		{
			_sight->turnX(LEFT);
		}

		if (bTurn[3])
		{
			_sight->turnX(RIGHT);
		}

		_eyeZ = -_sight->_z;
		_eyeX = -_sight->_x;
		_eyeY = -_sight->_y;
	}
}

void buildCamera()
{
	Matrix4x4 trans, rotX, rotY;
	rotX = rotateX(_sight->_rotate_y);
	rotY = rotateY(_sight->_rotate_x);
	trans = translate(_sight->_x, _sight->_y, _sight->_z);
	_viewMatrix = rotX * rotY * trans;
}

void buildProjectMatrix(int w, int h)
{
	_clipNear = 1.0f;
	float fAspect = (float)w / (float)h;
	_projectMatrix = perspective(60.0f, fAspect, _clipNear, 100.0f);
}

void initTextures()
{
	_texCube = new Texture("image/box.bmp");
	_texFloor = new Texture("image/floor.bmp");
}

void releaseTextures()
{
	delete _texCube;
	_texCube = nullptr;

	delete _texFloor;
	_texFloor = nullptr;
}
