#ifndef   __DATA__TYPE__H__
#define   __DATA__TYPE__H__

//��ɫ������
struct FrameBuffer
{
	unsigned char* colorBuffer;
	int width;
	int height;
};

//��Ȼ�����
struct DepthBuffer
{
	float* depthBuffer;
	int width;
	int height;
};

//����Ķ�������
struct Vertex
{
	float x, y, z, w;   //ģ�Ϳռ�����
	float nx, ny, nz;  //ģ�Ϳռ䷨������
	float s, t;       //��������

	Vertex() : x(0), y(0), z(0), w(1), nx(0), ny(0), nz(0), s(0), t(0){}

	Vertex(float vx, float vy, float vz,
		float vnx, float vny, float vnz,
		float vs, float vt) : x(vx), y(vy), z(vz), w(1.0f),
		nx(vnx), ny(vny), nz(vnz),
		s(vs), t(vt){}
};

//�����������
struct VertexOut
{
	float x, y, z, w;        //���ÿռ�����
	float wx, wy, wz, ww;   //����ռ�����
	float vx, vy, vz, vw;  //��ͼ�ռ�����
	float nx, ny, nz;     //����ռ䷨������
	float s, t;          //��������

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


//�����Ƭ������
struct Fragment
{
	float ndcX, ndcY, ndcZ;  //���ÿռ�����
	float wx, wy, wz, ww;   //����ռ�����
	float nx, ny, nz;      //����ռ䷨������
	float s, t;           //��������

	Fragment() : ndcX(0), ndcY(0), ndcZ(1.0f), 
		wx(0), wy(0), wz(0), ww(1.0f), 
		nx(0), ny(0), nz(0), 
		s(0), t(0){}
};

//Ƭ���������
struct FragmentOut
{
	float r, g, b, a; //��ɫֵr��g��b��a����ͨ��
	FragmentOut() : r(0), g(0), b(0), a(1.0f){}
};


void vertexCopy(Vertex* dst, Vertex* src);
void vertexOutCopy(VertexOut* dst, VertexOut* src);

//ģ��shader������shader����������
typedef void(*VertexShader)(Vertex input, VertexOut& output);
typedef void(*FragmentShader)(Fragment input, FragmentOut& output);
typedef void(*DrawCall)();

#endif