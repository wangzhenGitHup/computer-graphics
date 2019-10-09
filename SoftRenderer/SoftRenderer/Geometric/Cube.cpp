#include "Cube.h"

Cube::Cube()
{
	initVertex();
}

Cube::~Cube()
{
	delete[] _verts;
}

void Cube::initVertex()
{
	_verts = new Vertex[_cFaceNum * 3];
	//===========================
	_verts[0] = Vertex(
		1, -1, -1,
		0, 0, -1,
		1, 1);
	_verts[1] = Vertex(
		-1, -1, -1,
		0, 0, -1,
		0, 1);
	_verts[2] = Vertex(
		-1, 1, -1,
		0, 0, -1,
		0, 0);

	//=========================
	_verts[3] = Vertex(
		1, -1, -1,
		0, 0, -1,
		1, 1);
	_verts[4] = Vertex(
		-1, 1, -1,
		0, 0, -1,
		0, 0);
	_verts[5] = Vertex(
		1, 1, -1,
		0, 0, -1,
		1, 0);

	//============================
	_verts[6] = Vertex(
		-1, 1, 1,
		0, 0, 1,
		0, 0);
	_verts[7] = Vertex(
		-1, -1, 1,
		0, 0, 1,
		0, 1);
	_verts[8] = Vertex(
		1, -1, 1,
		0, 0, 1,
		1, 1);

	//=======================
	_verts[9] = Vertex(
		-1, 1, 1,
		0, 0, 1,
		0, 0);
	_verts[10] = Vertex(
		1, -1, 1,
		0, 0, 1,
		1, 1);
	_verts[11] = Vertex(
		1, 1, 1,
		0, 0, 1,
		1, 0);

	//==========================
	_verts[12] = Vertex(
		1, 1, 1,
		1, 0, 0,
		1, 0);
	_verts[13] = Vertex(
		1, -1, 1,
		1, 0, 0,
		1, 1);
	_verts[14] = Vertex(
		1, -1, -1,
		1, 0, 0,
		0, 1);

	//===========================
	_verts[15] = Vertex(
		1, 1, 1,
		1, 0, 0,
		1, 0);
	_verts[16] = Vertex(
		1, -1, -1,
		1, 0, 0,
		0, 1);
	_verts[17] = Vertex(
		1, 1, -1,
		1, 0, 0,
		0, 0);

	//==============================
	_verts[18] = Vertex(
		-1, -1, 1,
		-1, 0, 0,
		0, 1);
	_verts[19] = Vertex(
		-1, 1, 1,
		-1, 0, 0,
		0, 0);
	_verts[20] = Vertex(
		-1, 1, -1,
		-1, 0, 0,
		1, 0);

	//===================================
	_verts[21] = Vertex(
		-1, -1, 1,
		-1, 0, 0,
		0, 1);
	_verts[22] = Vertex(
		-1, 1, -1,
		-1, 0, 0,
		1, 0);
	_verts[23] = Vertex(
		-1, -1, -1,
		-1, 0, 0,
		1, 1);

	//==================================
	_verts[24] = Vertex(
		-1, 1, -1,
		0, 1, 0,
		0, 1);
	_verts[25] = Vertex(
		-1, 1, 1,
		0, 1, 0,
		0, 0);
	_verts[26] = Vertex(
		1, 1, 1,
		0, 1, 0,
		1, 0);

	//===================================
	_verts[27] = Vertex(
		-1, 1, -1,
		0, 1, 0,
		0, 1);
	_verts[28] = Vertex(
		1, 1, 1,
		0, 1, 0,
		1, 0);
	_verts[29] = Vertex(
		1, 1, -1,
		0, 1, 0,
		1, 1);

	//=================================
	_verts[30] = Vertex(
		1, -1, 1,
		0, -1, 0,
		1, 0);
	_verts[31] = Vertex(
		-1, -1, 1,
		0, -1, 0,
		0, 0);
	_verts[32] = Vertex(
		-1, -1, -1,
		0, -1, 0,
		0, 1);

	//===================================
	_verts[33] = Vertex(
		1, -1, 1,
		0, -1, 0,
		1, 0);
	_verts[34] = Vertex(
		-1, -1, -1,
		0, -1, 0,
		0, 1);
	_verts[35] = Vertex(
		1, -1, -1,
		0, -1, 0,
		1, 1);

}

void Cube::render(FrameBuffer* pFramebuffer, DepthBuffer* pDepthbuffer,
	VertexShader verShader, FragmentShader fsShader, 
	int cullFlag)
{
	drawFace(pFramebuffer, pDepthbuffer, verShader, fsShader, cullFlag, _verts, _cFaceNum);
}
