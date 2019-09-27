#ifndef  __FACE__H__
#define  __FACE__H__

#include "Tools.h"
#include "SelfMaths.h"
#include "SelfVector2D.h"
#include "SelfMatrix4x4.h"

class Face
{
public:
	Face(Vertex ma, Vertex mb, Vertex mc);
	Face();
	~Face();
	void copy2Face(Vertex a, Vertex b, Vertex c);
	void copy2FaceOut(VertexOut a, VertexOut b, VertexOut c);
	void calculateNDCVertex();
	void calculateClipMatrixInverse();


	Vertex _modelA, _modelB, _modelC;
	VertexOut _clipA, _clipB, _clipC;
	_Vector2D _ndcA, _ndcB, _ndcC;
	Matrix4x4 _clipMatrixInverse;
};
#endif