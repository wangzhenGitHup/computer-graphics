#include "Square.h"

Square::Square()
{
	initVerts();
}

Square::~Square()
{
	delete[]_verts;
	_verts = nullptr;
}

void Square::initVerts()
{
	//一个正方形面由2个三角形面组成，6个顶点

	//=========第1个三角形============
	_verts = new Vertex[_cFaceNum * 3];

	_verts[0] = Vertex(
		-1, 0, -1,
		0, 1, 0,
		0, 1
	);
	_verts[1] = Vertex(
		-1, 0, 1,
		0, 1, 0,
		0, 0
	);
	_verts[2] = Vertex(
		1, 0, 1,
		0, 1, 0,
		1, 0
	);

	//=========第2个三角形============
	_verts[3] = Vertex(
		1, 0, 1,
		0, 1, 0,
		1, 0
	);
	_verts[4] = Vertex(
		1, 0, -1,
		0, 1, 0,
		1, 1
	);
	_verts[5] = Vertex(
		-1, 0, -1,
		0, 1, 0,
		0, 1
	);
}

void Square::render(FrameBuffer* pFramebuffer, DepthBuffer* pDepthbuffer, 
	VertexShader vs, FragmentShader fs, 
	int cullFlag)
{
	drawFace(pFramebuffer, pDepthbuffer, vs, fs, cullFlag, _verts, _cFaceNum);
}

