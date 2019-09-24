#ifndef   __DATA__TYPE__H__
#define   __DATA__TYPE__H__

//颜色缓冲区
struct FrameBuffer
{
	unsigned char* colorBuffer;
	int width;
	int height;
};

//深度缓冲区
struct DepthBuffer
{
	float* depthBuffer;
	int width;
	int height;
};

//输入的顶点数据
struct Vertex
{
	float x, y, z, w;   //模型空间坐标
	float nx, ny, nz;  //模型空间法线坐标
	float s, t;       //纹理坐标

	Vertex() : x(0), y(0), z(0), w(1), nx(0), ny(0), nz(0), s(0), t(0){}

	Vertex(float vx, float vy, float vz,
		float vnx, float vny, float vnz,
		float vs, float vt) : x(vx), y(vy), z(vz), w(1.0f),
		nx(vnx), ny(vny), nz(vnz),
		s(vs), t(vt){}
};

//顶点输出数据
struct VertexOut
{
	float x, y, z, w;        //剪裁空间坐标
	float wx, wy, wz, ww;   //世界空间坐标
	float vx, vy, vz, vw;  //视图空间坐标
	float nx, ny, nz;     //世界空间法线坐标
	float s, t;          //纹理坐标

	VertexOut() : x(0), y(0), z(0), w(1.0f), 
		wx(0), wy(0), wz(0), ww(1.0f), 
		vx(0), vy(0), vz(0), vw(1.0f), 
		nx(0), ny(0), nz(0), 
		s(0), t(0){}

	VertexOut(float vx, float vy, float vz,
		float vwx, float vwy, float vwz,
		float vvx, float vvy, float vvz,
		float vnx, float vny, float vnz,
		float vs, float vt) : x(vx), y(vy), z(vz), w(1.0f), 
		wx(vwx), wy(vwy), wz(vwz), ww(1.0f),
		vx(vvx), vy(vvy), vz(vvz), vw(1.0f), 
		nx(vnx), ny(vny), nz(vnz), 
		s(vs), t(vt){}
};


//输入的片段数据
struct Fragment
{
	float ndcX, ndcY, ndcZ;  //剪裁空间坐标
	float wx, wy, wz, ww;   //世界空间坐标
	float nx, ny, nz;      //世界空间法线坐标
	float s, t;           //纹理坐标

	Fragment() : ndcX(0), ndcY(0), ndcZ(1.0f), 
		wx(0), wy(0), wz(0), ww(1.0f), 
		nx(0), ny(0), nz(0), 
		s(0), t(0){}
};

//片段输出数据
struct FragmentOut
{
	float r, g, b, a; //颜色值r、g、b、a分量通道
	FragmentOut() : r(0), g(0), b(0), a(1.0f){}
};


void vertexCopy(Vertex* dst, Vertex* src);
void vertexOutCopy(VertexOut* dst, VertexOut* src);

//模拟shader，定义shader函数的类型
typedef void(*VertexShader)(Vertex input, VertexOut& output);
typedef void(*FragmentShader)(Fragment input, FragmentOut& output);
typedef void(*DrawCall)();

#endif