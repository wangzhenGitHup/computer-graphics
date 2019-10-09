#ifndef  __SQUARE__H__
#define  __SQUARE__H__

#include "Graphic.h"

class Square
{
public:
	Square();
	~Square();
	void render(FrameBuffer* pFramebuffer, DepthBuffer* pDepthbuffer, 
		VertexShader vs, FragmentShader fs, 
		int cullFlag);
	Vertex* getVertexs(){ return _verts; }

private:
	void initVerts();

private:
	Vertex* _verts;
	const int _cFaceNum = 2;
};
#endif