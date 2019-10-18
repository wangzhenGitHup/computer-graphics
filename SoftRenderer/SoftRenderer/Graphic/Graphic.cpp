#include "Graphic.h"
#include "Utils.h"
#include "SelfMaths.h"

float _eyeX, _eyeY, _eyeZ, _clipNear;
Face* _pFace1;
Face* _pFace2;
bool _bBlendFlag = false;
FrameBuffer* _pFrontBuffer = nullptr;
FrameBuffer* _pBackBuffer = nullptr;
FrameBuffer* _pFrameBuffer1 = nullptr;
FrameBuffer* _pFrameBuffer2 = nullptr;
DepthBuffer* _pDepthBuffer = nullptr;
unsigned char* _pScreenBits = nullptr;
bool _bBuffersReady = false;

void initFrameBuffer(FrameBuffer** pFrameBuffer, int width, int height)
{
	*pFrameBuffer = (FrameBuffer*)malloc(sizeof(FrameBuffer));
	(*pFrameBuffer)->width = width;
	(*pFrameBuffer)->height = height;
	(*pFrameBuffer)->colorBuffer = new unsigned char[width * height * 3];
	memset((*pFrameBuffer)->colorBuffer, 0, sizeof(unsigned char)* width * height * 3);
}

void releaseFrameBuffer(FrameBuffer** pFrameBuffer)
{
	if (!(*pFrameBuffer))
	{
		return;
	}

	delete[](*pFrameBuffer)->colorBuffer;
	(*pFrameBuffer)->colorBuffer = nullptr;

	free(*pFrameBuffer);
	*pFrameBuffer = nullptr;
}

void initDepthBuffer(DepthBuffer** pDepthBuffer, int width, int height)
{
	*pDepthBuffer = (DepthBuffer*)malloc(sizeof(DepthBuffer));
	(*pDepthBuffer)->width = width;
	(*pDepthBuffer)->height = height;
	(*pDepthBuffer)->depthBuffer = new float[width * height];
	memset((*pDepthBuffer)->depthBuffer, 0, sizeof(float)* width * height);
}

void releaseDepthBuffer(DepthBuffer** pDepthBuffer)
{
	if (!(*pDepthBuffer))
	{
		return;
	}

	delete[](*pDepthBuffer)->depthBuffer;
	(*pDepthBuffer)->depthBuffer = nullptr;

	free(*pDepthBuffer);
	*pDepthBuffer = nullptr;
}

void initDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer,
	int width, int height)
{
	initFrameBuffer(pFrameBuffer, width, height);
	initDepthBuffer(pDepthBuffer, width, height);
}

void releaseDevice(FrameBuffer** pFrameBuffer, DepthBuffer** pDepthBuffer)
{
	releaseFrameBuffer(pFrameBuffer);
	releaseDepthBuffer(pDepthBuffer);
}

void initDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer, int width, int height)
{
	initFrameBuffer(pFrameBuffer1, width, height);
	initFrameBuffer(pFrameBuffer2, width, height);
	initDepthBuffer(pDepthBuffer, width, height);

	_pFrontBuffer = *pFrameBuffer1;
	_pBackBuffer = *pFrameBuffer2;
	_bBuffersReady = false;
}

void releaseDevice2Buffer(FrameBuffer** pFrameBuffer1, FrameBuffer** pFrameBuffer2,
	DepthBuffer** pDepthBuffer)
{
	_pFrontBuffer = nullptr;
	_pBackBuffer = nullptr;
	releaseFrameBuffer(pFrameBuffer1);
	releaseFrameBuffer(pFrameBuffer2);
	releaseDepthBuffer(pDepthBuffer);
}

void clearScreen(FrameBuffer* pFrameBuffer,
	unsigned char red, unsigned char green, unsigned char blue)
{
	for (int i = 0; i < pFrameBuffer->height; i++)
	{
		for (int j = 0; j < pFrameBuffer->width; j++)
		{
			int idx = (i * pFrameBuffer->width + j) * 3;
			pFrameBuffer->colorBuffer[idx] = red;
			pFrameBuffer->colorBuffer[idx + 1] = green;
			pFrameBuffer->colorBuffer[idx + 2] = blue;
		}
	}
}

void clearScreenFast(FrameBuffer* pFrameBuffer, unsigned char color)
{
	int size = pFrameBuffer->width * pFrameBuffer->height * 3;
	memset(pFrameBuffer->colorBuffer, color * sizeof(unsigned char), size);
}

void clearDepth(DepthBuffer* pDepthBuffer)
{
	//深度缓冲默认置为1
	for (int i = 0; i < pDepthBuffer->height; i++)
	{
		for (int j = 0; j < pDepthBuffer->width; j++)
		{
			pDepthBuffer->depthBuffer[i * pDepthBuffer->width + j] = 1.0f;
		}
	}
}

void flush(FrameBuffer* pFrameBuffer)
{
	//将颜色缓冲中的值赋给屏幕
	for (int i = 0; i < pFrameBuffer->height; i++)
	{
		for (int j = 0; j < pFrameBuffer->width; j++)
		{
			int idx = (i * pFrameBuffer->width + j) * 3;
			unsigned char red = pFrameBuffer->colorBuffer[idx];
			unsigned char green = pFrameBuffer->colorBuffer[idx + 1];
			unsigned char blue = pFrameBuffer->colorBuffer[idx + 2];

			_pScreenBits[idx] = blue;
			_pScreenBits[idx + 1] = green;
			_pScreenBits[idx + 2] = red;
		}
	}
}

void swapBuffer()
{
	//双缓冲交换，并将要显示的缓冲颜色值赋给屏幕显示
	if (_pFrontBuffer == _pFrameBuffer1)
	{
		_pFrontBuffer = _pFrameBuffer2;
		_pBackBuffer = _pFrameBuffer1;
	}
	else
	{
		_pFrontBuffer = _pFrameBuffer1;
		_pBackBuffer = _pFrameBuffer2;
	}

	if (!_bBuffersReady)
	{
		_bBuffersReady = true;
		return;
	}

	FrameBuffer* pFrameBuf = _pFrontBuffer;
	for (int i = 0; i < pFrameBuf->height; i++)
	{
		for (int j = 0; j < pFrameBuf->width; j++)
		{
			int idx = (i * pFrameBuf->width + j) * 3;
			unsigned char red = pFrameBuf->colorBuffer[idx];
			unsigned char green = pFrameBuf->colorBuffer[idx + 1];
			unsigned char blue = pFrameBuf->colorBuffer[idx + 2];
			_pScreenBits[idx] = blue;
			_pScreenBits[idx + 1] = green;
			_pScreenBits[idx + 2] = red;
		}
	}
}

void convertToScreen(int height, int& sy)
{
	//y轴翻转
	sy = height - 1 - sy;
}

bool cullFace(Face* pFace, int flag)
{
	//在世界空间进行背面剔出操作，为了省去不必要的顶点坐标从世界到视图空间的变化

	//面向量
	_Vector3D faceNormal(pFace->_clipA.nx, pFace->_clipA.ny, pFace->_clipA.nz);
	//视线到面的向量
	_Vector3D eyeVec(_eyeX - pFace->_clipA.wx,
		_eyeY - pFace->_clipA.wy,
		_eyeZ - pFace->_clipA.wz);

	//计算向量的点积，背面：点积小于0，需要剔除，正面：点积大于0，需要剔除
	float dotValue = eyeVec.Dot(faceNormal);

	if (CULL_BACK == flag)
	{
		if (dotValue < 0 || FLT_IS_ZERO(dotValue))
		{
			return true;
		}
		return false;
	}
	else if (CULL_FRONT == flag)
	{
		if (dotValue > 0 || FLT_IS_ZERO(dotValue))
		{
			return true;
		}
		return false;
	}

	return false;
}

void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	int& screenX, int& screenY)
{
	//从屏幕中心开始变化
	// Xscreen = (ndcX + 1) * (SCREEN_WIDTH - 1) * 0.5
	// Yscreen = (ndcY + 1) * (SCREEN_HEIGHT - 1) * 0.5
	float offsetX = (ndcX + 1.0f) * 0.5f;
	float offsetY = (ndcY + 1.0f) * 0.5f;
	screenX = (int)(Roundf(offsetX * (width - 1.0f)));
	screenY = (int)(Roundf(offsetY * (height - 1.0f)));
}

void viewPortTransform(float ndcX, float ndcY,
	float width, float height,
	float& screenX, float& screenY)
{
	//从屏幕中心开始变化
	// Xscreen = (ndcX + 1) * (SCREEN_WIDTH - 1) * 0.5
	// Yscreen = (ndcY + 1) * (SCREEN_HEIGHT - 1) * 0.5
	float offsetX = (ndcX + 1.0f) * 0.5f;
	float offsetY = (ndcY + 1.0f) * 0.5f;
	screenX = offsetX * (width - 1.0f);
	screenY = offsetY * (height - 1.0f);
}

void inverseViewPortTransform(int screenX, int screenY,
	float width, float height,
	float& ndcX, float& ndcY)
{
	float scaleX = (float)screenX / (width - 1.0f);
	float scaleY = (float)screenY / (height - 1.0f);
	ndcX = scaleX * 2.0f - 1.0f;
	ndcY = scaleY * 2.0f - 1.0f;
}

void rasterize(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	FragmentShader fs, Face* face)
{
	float ndcX = 0, ndcY = 0, clipW = 0;
	float scrAX, scrAY, scrBX, scrBY, scrCX, scrCY;

	//得到3个二维坐标，3个顶点最终在屏幕上的位置
	viewPortTransform(face->_ndcA.GetX(), face->_ndcA.GetY(),
		(float)pFrameBuffer->width, (float)pFrameBuffer->height,
		scrAX, scrAY);
	viewPortTransform(face->_ndcB.GetX(), face->_ndcB.GetY(),
		(float)pFrameBuffer->width, (float)pFrameBuffer->height,
		scrBX, scrBY);
	viewPortTransform(face->_ndcC.GetX(), face->_ndcC.GetY(),
		(float)pFrameBuffer->width, (float)pFrameBuffer->height,
		scrCX, scrCY);

	//退化为直线不进行光栅化
	if (FLT_EQUAL(scrAY, scrBY) && FLT_EQUAL(scrAY, scrCY))
	{
		return;
	}

	//求y的范围
	int minY = (int)max(0, min(scrAY, min(scrBY, scrCY)));
	int maxY = (int)min(pFrameBuffer->height - 1, max(scrAY, max(scrBY, scrCY)));

	for (int startY = minY; startY <= maxY; startY++)
	{
		float x1, x2;
		//检查三角形，调整x坐标
		calculateBounds(scrAX, scrAY,
			scrBX, scrBY,
			scrCX, scrCY,
			(float)startY,
			x1, x2);

		//取最小x值
		int minX = (int)max(0, Roundf(min(x1, x2)));
		//取最大x值
		int maxX = (int)min(pFrameBuffer->width - 1, Roundf(max(x1, x2)));

		//从左到右扫描
		//用重心坐标法光栅化
		for (int startX = minX; startX <= maxX; startX++)
		{
			//逆视口变换，得到片段对应的标准化空间坐标
			inverseViewPortTransform(startX, startY,
				(float)pFrameBuffer->width, (float)pFrameBuffer->height,
				ndcX, ndcY);

			_Vector4D ndcPixel(ndcX, ndcY, 1.0f, 0.0f);
			//剪裁空间下坐标
			_Vector4D proportion4D = face->_clipMatrixInverse * ndcPixel;
			_Vector3D proportionFragment(proportion4D.GetX(), proportion4D.GetY(), proportion4D.GetZ());

			float pa = proportionFragment.GetX();
			float pb = proportionFragment.GetY();
			float pc = proportionFragment.GetZ();
			if (pa < 0.0f || pb < 0.0f || pc < 0.0f)
			{
				continue;
			}

			float sum = pa + pb + pc; //和为1.0
			float inverseSum = 1.0f / sum;
			pa *= inverseSum;
			pb *= inverseSum;
			pc *= inverseSum;

			//计算3个顶点对片段产生影响的权重
			Fragment frag;
			interpolate3f(pa, pb, pc,
				face->_clipA.w, face->_clipB.w, face->_clipC.w,
				clipW);
			interpolate3f(pa, pb, pc,
				face->_clipA.z, face->_clipB.z, face->_clipC.z,
				frag.ndcZ);

			//齐次映射后 坐标z的值
			float inverseClipW = 1.0f / clipW;
			frag.ndcZ *= inverseClipW;

			//z的值不在深度值范围内
			if (frag.ndcZ < -1.0f || frag.ndcZ > 1.0f)
			{
				continue;
			}

			if (pDepthBuffer != nullptr)
			{
				//深度测试，只有当前片段的深度值小于等于深度缓冲中的值才将当前片段的深度值写入到深度缓冲中
				float storeZ = readDepth(pDepthBuffer, startX, startY);
				if (storeZ < frag.ndcZ)
				{
					continue;
				}

				//向深度缓冲中写入新的深度值
				writeDepth(pDepthBuffer, startX, startY, frag.ndcZ);
			}

			//对剪裁空间x值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.x, face->_clipB.x, face->_clipC.x,
				frag.ndcX);
			frag.ndcX *= inverseClipW;

			//对剪裁空间y值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.y, face->_clipB.y, face->_clipC.y,
				frag.ndcY);
			frag.ndcY *= inverseClipW;

			//对世界空间x值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.wx, face->_clipB.wx, face->_clipC.wx,
				frag.wx);

			//对世界空间y值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.wy, face->_clipB.wy, face->_clipC.wy,
				frag.wy);

			//对世界空间z值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.wz, face->_clipB.wz, face->_clipC.wz,
				frag.wz);

			//对世界空间w值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.ww, face->_clipB.ww, face->_clipC.ww,
				frag.ww);

			//对世界空间法线x值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.nx, face->_clipB.nx, face->_clipC.nx,
				frag.nx);

			//对世界空间法线y值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.ny, face->_clipB.ny, face->_clipC.ny,
				frag.ny);

			//对世界空间法线z值进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.nz, face->_clipB.nz, face->_clipC.nz,
				frag.nz);

			//对纹理坐标进行按权重插值运算
			interpolate3f(pa, pb, pc,
				face->_clipA.s, face->_clipB.s, face->_clipC.s,
				frag.s);
			interpolate3f(pa, pb, pc,
				face->_clipA.t, face->_clipB.t, face->_clipC.t,
				frag.t);


			//片段输出值
			FragmentOut outFrag;
			fs(frag, outFrag);

			unsigned char cr = 255, cg = 255, cb = 255, sr = 255, sg = 255, sb = 255;
			normalizeColor(outFrag.r, outFrag.g, outFrag.b, cr, cg, cb);
			//是否要颜色混合
			if (_bBlendFlag)
			{
				readFrameBuffer(pFrameBuffer, startX, startY, sr, sg, sb);
				BlendData blendData;
				blendData.srcR = cr;
				blendData.srcG = cg;
				blendData.srcB = cb;
				blendData.srcA = outFrag.a;
				blendData.dstR = sr;
				blendData.dstG = sg;
				blendData.dstB = sb;
				blend(blendData, cr, cg, cb);
			}

			//更新颜色缓冲
			drawPixel(pFrameBuffer, startX, startY, cr, cg, cb);
		}

	}
}

void calculateBounds(float scrAX, float scrAY,
	float scrBX, float scrBY,
	float scrCX, float scrCY,
	float startY, float& x1, float& x2)
{
	//根据直线的参数化方程求得x坐标  p = p0 + (p1 - p0) * factor;
	//factor = p - p0 / p1 - p0;
	//因为y值是已知的，可求得因子factor

	//平顶三角形和平底三角形情况
	if (scrAY == scrBY) //平顶
	{
		float paramAC = (startY - scrAY) / (scrCY - scrAY);//直线ac
		float paramBC = (startY - scrBY) / (scrCY - scrBY);//直线bc
		x1 = (scrCX - scrAX) * paramAC + scrAX;
		x2 = (scrCX - scrBX) * paramBC + scrBX;
	}
	else if (scrAY == scrCY) //平顶
	{
		float paramAB = (startY - scrAY) / (scrBY - scrAY); //直线ab
		float paramBC = (startY - scrBY) / (scrCY - scrBY); //直线bc
		x1 = (scrBX - scrAX) * paramAB + scrAX;
		x2 = (scrCX - scrBX) * paramBC + scrBX;
	}
	else if (scrBY == scrCY) //平底
	{
		float paramAB = (startY - scrAY) / (scrBY - scrAY); //直线ab
		float paramAC = (startY - scrAY) / (scrCY - scrAY); //直线ac
		x1 = (scrBX - scrAX) * paramAB + scrAX;
		x2 = (scrCX - scrAX) * paramAC + scrAX;
	}
	else //常规三角形
	{
		float paramAB = (startY - scrAY) / (scrBY - scrAY); //直线ab
		float paramAC = (startY - scrAY) / (scrCY - scrAY); //直线ac
		float paramBC = (startY - scrBY) / (scrCY - scrBY); //直线bc

		//检测当前y值在不在直线AB上
		bool bOnABLine = ((paramAB < 1.0f || FLT_EQUAL(paramAB, 1.0f)) && (paramAB > 0.0f || FLT_IS_ZERO(paramAB))) ? true : false;
		//检测当前y值在不在直线AC上
		bool bOnACLine = ((paramAC < 1.0f || FLT_EQUAL(paramAC, 1.0f)) && (paramAC > 0.0f || FLT_IS_ZERO(paramAC))) ? true : false;
		//检测当前y值在不在直线BC上
		bool bOnBCLine = ((paramBC < 1.0f || FLT_EQUAL(paramBC, 1.0f)) && (paramBC > 0.0f || FLT_IS_ZERO(paramBC))) ? true : false;

		float xAB = (scrBX - scrAX) * paramAB + scrAX;
		float xAC = (scrCX - scrAX) * paramAC + scrAX;
		float xBC = (scrCX - scrBX) * paramBC + scrBX;

		if (!bOnABLine) //不在直线AB上
		{
			x1 = xAC;
			x2 = xBC;
		}
		else if (!bOnACLine) //不在直线AC上
		{
			x1 = xAB;
			x2 = xBC;
		}
		else if (!bOnBCLine) //不在直线BC上
		{
			x1 = xAB;
			x2 = xAC;
		}
		else
		{
			//随便赋值任意2条直线上的x点
			x1 = xAC;
			x2 = xBC;

			//排除2直线交点的情况
			if (FLT_EQUAL(x1, x2))
			{
				x2 = xAB;
			}
		}
	}
}

void blend(BlendData& blendData,
	unsigned char& finalR, unsigned char& finalG, unsigned char& finalB)
{
	float dstA = 1.0f - blendData.srcA;
	float R = (float)blendData.srcR * blendData.srcA + (float)blendData.dstR * dstA;
	float G = (float)blendData.srcG * blendData.srcA + (float)blendData.dstG * dstA;
	float B = (float)blendData.srcB * blendData.srcA + (float)blendData.dstB * dstA;

	finalR = (unsigned char)(R > 255 ? 255 : R);
	finalG = (unsigned char)(G > 255 ? 255 : G);
	finalB = (unsigned char)(B > 255 ? 255 : B);
}

void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Vertex* pVertexBuffer, int count)
{
	//批量提交顶点组织成三角形面，批量渲染
	for (int i = 0; i < count; i++)
	{
		Face pFace(pVertexBuffer[i * 3], pVertexBuffer[i * 3 + 1], pVertexBuffer[i * 3 + 2]);
		drawFace(pFrameBuffer, pDepthBuffer, vs, fs, cullFlag, &pFace);
	}
}

void drawFace(FrameBuffer* pFrameBuffer, DepthBuffer* pDepthBuffer,
	VertexShader vs, FragmentShader fs,
	int cullFlag, Face* pFace)
{
	vs(pFace->_modelA, pFace->_clipA);
	vs(pFace->_modelB, pFace->_clipB);
	vs(pFace->_modelC, pFace->_clipC);

	//剔除面操作
	if (cullFace(pFace, cullFlag))
	{
		return;
	}

	//检测三角形3个顶点与近剪裁面的关系
	int clipFlag = checkFace(pFace);
	if (clipFlag != ALL_NOT_VERTEX_AFTER_NEAR_CLIP)
	{
		if (clipFlag == ALL_VERTEX_AFTER_NEAR_CLIP)
		{
			return;
		}

		//重新划分原三角形
		fixFace(pFace, clipFlag);
		if (!cullFace(_pFace1, cullFlag))
		{
			_pFace1->calculateClipMatrixInverse();
			_pFace1->calculateNDCVertex();
			rasterize(pFrameBuffer, pDepthBuffer, fs, _pFace1);
		}

		//只有一点小于剪裁面，原三角形将被分割成2个新三角形
		//上面已经对其中一个新三角形进行了面剔除和光栅化了，
		//还要对第2个新三角形进行同样的操作
		if (clipFlag == A_VERTEX_AFTER_NEAR_CLIP ||
			clipFlag == B_VERTEX_AFTER_NEAR_CLIP ||
			clipFlag == C_VERTEX_AFTER_NEAR_CLIP)
		{
			if (!cullFace(_pFace2, cullFlag))
			{
				_pFace2->calculateClipMatrixInverse();
				_pFace2->calculateNDCVertex();
				rasterize(pFrameBuffer, pDepthBuffer, fs, _pFace2);
			}
		}
	}
	else if (clipFlag == ALL_NOT_VERTEX_AFTER_NEAR_CLIP)
	{
		pFace->calculateClipMatrixInverse();
		pFace->calculateNDCVertex();
		rasterize(pFrameBuffer, pDepthBuffer, fs, pFace);
	}
}

void drawPixel(FrameBuffer* pFrameBuffer,
	int x, int y,
	unsigned char r, unsigned char g, unsigned char b)
{
	convertToScreen(pFrameBuffer->height, y);
	int idx = (y * pFrameBuffer->width + x) * 3;
	pFrameBuffer->colorBuffer[idx] = r;
	pFrameBuffer->colorBuffer[idx + 1] = g;
	pFrameBuffer->colorBuffer[idx + 2] = b;
}

void readFrameBuffer(FrameBuffer* pFrameBuffer,
	int x, int y,
	unsigned char& r, unsigned char& g, unsigned char& b)
{
	convertToScreen(pFrameBuffer->height, y);
	int idx = (y * pFrameBuffer->width + x) * 3;
	r = pFrameBuffer->colorBuffer[idx];
	g = pFrameBuffer->colorBuffer[idx + 1];
	b = pFrameBuffer->colorBuffer[idx + 2];
}

void writeDepth(DepthBuffer* pDepthBuffer, int x, int y, float depth)
{
	convertToScreen(pDepthBuffer->height, y);
	pDepthBuffer->depthBuffer[y * pDepthBuffer->width + x] = depth;
}

float readDepth(DepthBuffer* depthBuffer, int x, int y)
{
	convertToScreen(depthBuffer->height, y);
	return depthBuffer->depthBuffer[y * depthBuffer->width + x];
}

void normalizeColor(float r, float g, float b,
	unsigned char& red, unsigned char& green, unsigned char& blue)
{
	r *= 255.0f;
	g *= 255.0f;
	b *= 255.0f;
	red = (unsigned char)(r > 255 ? 255 : r);
	green = (unsigned char)(g > 255 ? 255 : g);
	blue = (unsigned char)(b > 255 ? 255 : b);
}

void initFixFace()
{
	_pFace1 = new Face();
	_pFace2 = new Face();
}

void releaseFixFace()
{
	delete _pFace1;
	_pFace1 = nullptr;

	delete _pFace2;
	_pFace2 = nullptr;
}

int checkFace(Face* pFace)
{
	bool bFailA = false;
	bool bFailB = false;
	bool bFailC = false;
	int iFailVertexCnt = 0;

	//齐次映射后 坐标z的值 是否小于 近剪裁面
	if (pFace->_clipA.vz / pFace->_clipA.vw > -_clipNear)
	{
		bFailA = true;
		iFailVertexCnt++;
	}

	if (pFace->_clipB.vz / pFace->_clipB.vw > -_clipNear)
	{
		bFailB = true;
		iFailVertexCnt++;
	}

	if (pFace->_clipC.vz / pFace->_clipC.vw > -_clipNear)
	{
		bFailC = true;
		iFailVertexCnt++;
	}

	if (3 == iFailVertexCnt)
	{
		return ALL_VERTEX_AFTER_NEAR_CLIP;
	}

	if (0 == iFailVertexCnt)
	{
		return ALL_NOT_VERTEX_AFTER_NEAR_CLIP;
	}

	if (2 == iFailVertexCnt)
	{
		if (bFailA && bFailB)
		{
			return AB_VERTEX_AFTER_NEAR_CLIP;
		}

		if (bFailA && bFailC)
		{
			return AC_VERTEX_AFTER_NEAR_CLIP;
		}

		if (bFailB && bFailC)
		{
			return BC_VERTEX_AFTER_NEAR_CLIP;
		}
	}
	else if (1 == iFailVertexCnt)
	{
		if (bFailA)
		{
			return A_VERTEX_AFTER_NEAR_CLIP;
		}

		if (bFailB)
		{
			return B_VERTEX_AFTER_NEAR_CLIP;
		}

		if (bFailC)
		{
			return C_VERTEX_AFTER_NEAR_CLIP;
		}
	}

	return ALL_VERTEX_AFTER_NEAR_CLIP;
}

void fixFace(Face* pFace, int fixFlag)
{
	switch (fixFlag)
	{
	case A_VERTEX_AFTER_NEAR_CLIP:
		fix1FailFace(pFace->_clipA, pFace->_clipB, pFace->_clipC);
		break;

	case B_VERTEX_AFTER_NEAR_CLIP:
		fix1FailFace(pFace->_clipB, pFace->_clipA, pFace->_clipC);
		break;

	case C_VERTEX_AFTER_NEAR_CLIP:
		fix1FailFace(pFace->_clipC, pFace->_clipA, pFace->_clipB);
		break;

	case AB_VERTEX_AFTER_NEAR_CLIP:
		fix2FailFace(pFace->_clipA, pFace->_clipB, pFace->_clipC);
		break;

	case AC_VERTEX_AFTER_NEAR_CLIP:
		fix2FailFace(pFace->_clipA, pFace->_clipC, pFace->_clipB);
		break;

	case BC_VERTEX_AFTER_NEAR_CLIP:
		fix2FailFace(pFace->_clipB, pFace->_clipC, pFace->_clipA);
		break;
	}
}

void fix1FailFace(VertexOut failVertex, VertexOut succVertex1, VertexOut succVertex2)
{
	float inverseFailW = 1.0f / failVertex.vw;
	float inverseSucc1W = 1.0f / succVertex1.vw;
	float inverseSucc2W = 1.0f / succVertex2.vw;

	_Vector3D failVec3(failVertex.vx * inverseFailW,
		failVertex.vy * inverseFailW,
		failVertex.vz * inverseFailW);

	_Vector3D succ1_vec3(succVertex1.vx * inverseSucc1W,
		succVertex1.vy * inverseSucc1W,
		succVertex1.vz * inverseSucc1W);

	_Vector3D succ2_vec3(succVertex2.vx * inverseSucc2W,
		succVertex2.vy * inverseSucc2W,
		succVertex2.vz * inverseSucc2W);

	//求小于近剪裁面的点的直线 与 在近剪裁面内的一个点所在平面的交点
	float param1 = calZPara(failVec3.GetZ(), succ1_vec3.GetZ(), -_clipNear);
	_Vector3D interPoint1 = calcParaVec(failVec3, succ1_vec3, param1);

	//分别求得 交点到2点的距离
	float len1 = (failVec3 - interPoint1).GetLength();
	float len2 = (succ1_vec3 - interPoint1).GetLength();

	//归并为和为1.0
	float sum = len1 + len2;
	float inverSum = 1.0f / sum;
	len1 *= inverSum;
	len2 *= inverSum;

	//插值计算出新的顶点
	VertexOut newVertex1;
	interpolate2v(len1, len2, succVertex1, failVertex, newVertex1);

	//=====================与第2个点进行同上计算============================
	float param2 = calZPara(failVec3.GetZ(), succ2_vec3.GetZ(), -_clipNear);
	_Vector3D interPoint2 = calcParaVec(failVec3, succ2_vec3, param2);
	len1 = (failVec3 - interPoint2).GetLength();
	len2 = (succ2_vec3 - interPoint2).GetLength();

	sum = len1 + len2;
	inverSum = 1.0f / sum;
	len1 *= inverSum;
	len2 *= inverSum;

	VertexOut newVertex2;
	interpolate2v(len1, len2, succVertex2, failVertex, newVertex2);

	_pFace1->copy2FaceOut(succVertex1, newVertex1, newVertex2);
	_pFace2->copy2FaceOut(succVertex2, succVertex1, newVertex2);
}

void fix2FailFace(VertexOut failVertex1, VertexOut failVertex2, VertexOut succVertex)
{
	float invFail1W = 1.0f / failVertex1.vw;
	float invFail2W = 1.0f / failVertex2.vw;
	float invSuccW = 1.0f / succVertex.vw;

	_Vector3D fail1_vec3(failVertex1.vx * invFail1W,
		failVertex1.vy * invFail1W,
		failVertex1.vz * invFail1W);

	_Vector3D fail2_vec3(failVertex2.vx * invFail2W,
		failVertex2.vy * invFail2W,
		failVertex2.vz * invFail2W);

	_Vector3D succ_vec3(succVertex.vx * invSuccW,
		succVertex.vy * invSuccW,
		succVertex.vz * invSuccW);

	float param1 = calZPara(fail1_vec3.GetZ(), succ_vec3.GetZ(), -_clipNear);
	_Vector3D interPoint1 = calcParaVec(fail1_vec3, succ_vec3, param1);

	float len1 = (fail1_vec3 - interPoint1).GetLength();
	float len2 = (succ_vec3 - interPoint1).GetLength();
	float sum = len1 + len2;
	float invSum = 1.0f / sum;
	len1 *= invSum;
	len2 *= invSum;

	VertexOut newVertex1;
	interpolate2v(len1, len2, succVertex, failVertex1, newVertex1);

	float param2 = calZPara(fail2_vec3.GetZ(), succ_vec3.GetZ(), -_clipNear);
	_Vector3D interPoint2 = calcParaVec(fail2_vec3, succ_vec3, param2);
	len1 = (fail2_vec3 - interPoint2).GetLength();
	len2 = (succ_vec3 - interPoint2).GetLength();
	sum = len1 + len2;
	invSum = 1.0f / sum;
	len1 *= invSum;
	len2 *= invSum;

	VertexOut newVertex2;
	interpolate2v(len1, len2, succVertex, failVertex2, newVertex2);

	_pFace1->copy2FaceOut(succVertex, newVertex1, newVertex2);
}

void interpolate2v(float pa, float pb,
	VertexOut vertex1, VertexOut vertex2,
	VertexOut& result)
{
	//插值计算所有新坐标点
	interpolate2f(pa, pb, vertex1.x, vertex2.x, result.x);
	interpolate2f(pa, pb, vertex1.y, vertex2.y, result.y);
	interpolate2f(pa, pb, vertex1.z, vertex2.z, result.z);
	interpolate2f(pa, pb, vertex1.w, vertex2.w, result.w);

	interpolate2f(pa, pb, vertex1.wx, vertex2.wx, result.wx);
	interpolate2f(pa, pb, vertex1.wy, vertex2.wy, result.wy);
	interpolate2f(pa, pb, vertex1.wz, vertex2.wz, result.wz);
	interpolate2f(pa, pb, vertex1.ww, vertex2.ww, result.ww);

	interpolate2f(pa, pb, vertex1.vx, vertex2.vx, result.vx);
	interpolate2f(pa, pb, vertex1.vy, vertex2.vy, result.vy);
	interpolate2f(pa, pb, vertex1.vz, vertex2.vz, result.vz);
	interpolate2f(pa, pb, vertex1.vw, vertex2.vw, result.vw);

	interpolate2f(pa, pb, vertex1.nx, vertex2.nx, result.nx);
	interpolate2f(pa, pb, vertex1.ny, vertex2.ny, result.ny);
	interpolate2f(pa, pb, vertex1.nz, vertex2.nz, result.nz);

	interpolate2f(pa, pb, vertex1.s, vertex2.s, result.s);
	interpolate2f(pa, pb, vertex1.t, vertex2.t, result.t);
}
