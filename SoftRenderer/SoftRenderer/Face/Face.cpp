#include "Face.h"

Face::Face(Vertex ma, Vertex mb, Vertex mc)
{
	_modelA = ma;
	_modelB = mb;
	_modelC = mc;

	_clipMatrixInverse.LoadIdentity();
}

Face::Face()
{
	_clipMatrixInverse.LoadIdentity();
}

Face::~Face()
{

}

void Face::copy2Face(Vertex a, Vertex b, Vertex c)
{
	vertexCopy(&_modelA, &a);
	vertexCopy(&_modelB, &b);
	vertexCopy(&_modelC, &c);
}

void Face::copy2FaceOut(VertexOut a, VertexOut b, VertexOut c)
{
	vertexOutCopy(&_clipA, &a);
	vertexOutCopy(&_clipB, &b);
	vertexOutCopy(&_clipC, &c);
}

void Face::calculateNDCVertex()
{
	float invClipAW = 1.0f / _clipA.w;
	float invClipBW = 1.0f / _clipB.w;
	float invClipCW = 1.0f / _clipC.w;

	_ndcA.SetX(_clipA.x * invClipAW);
	_ndcA.SetY(_clipA.y * invClipAW);

	_ndcB.SetX(_clipB.x * invClipBW);
	_ndcB.SetY(_clipB.y * invClipBW);

	_ndcC.SetX(_clipC.x * invClipCW);
	_ndcC.SetY(_clipC.y * invClipCW);
}

void Face::calculateClipMatrixInverse()
{
	_clipMatrixInverse.LoadIdentity();

	_clipMatrixInverse.SetElement(0, _clipA.x);
	_clipMatrixInverse.SetElement(1, _clipA.y);
	_clipMatrixInverse.SetElement(2, _clipA.w);

	_clipMatrixInverse.SetElement(4, _clipB.x);
	_clipMatrixInverse.SetElement(5, _clipB.y);
	_clipMatrixInverse.SetElement(6, _clipB.w);

	_clipMatrixInverse.SetElement(8, _clipC.x);
	_clipMatrixInverse.SetElement(9, _clipC.y);
	_clipMatrixInverse.SetElement(10, _clipC.w);

	_clipMatrixInverse.Inverse();
}
