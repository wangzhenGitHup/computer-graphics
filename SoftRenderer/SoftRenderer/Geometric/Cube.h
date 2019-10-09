#ifndef  __CUBE__H__
#define  __CUBE__H__

#include "Graphic.h"

class Cube
{
public:
	Cube();
	~Cube();
	void render(FrameBuffer* pFramebuffer, DepthBuffer* pDepthbuffer, 
		VertexShader verShader, FragmentShader fsShader, 
		int cullFlag);
	Vertex* getVertexs(){ return _verts; }

private:
	void initVertex();

private:
	const int _cFaceNum = 12;
	Vertex* _verts;
};

#endif