#include "DataType.h"


void vertexCopy(Vertex* dst, Vertex* src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->w = src->w;
	dst->nx = src->nx;
	dst->ny = src->ny;
	dst->nz = src->nz;
	dst->s = src->s;
	dst->t = src->t;
}


void vertexOutCopy(VertexOut* dst, VertexOut* src)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->w = src->w;
	dst->wx = src->wx;
	dst->wy = src->wy;
	dst->wz = src->wz;
	dst->ww = src->ww;
	dst->vx = src->vx;
	dst->vy = src->vy;
	dst->vz = src->vz;
	dst->vw = src->vw;
	dst->nx = src->nx;
	dst->ny = src->ny;
	dst->nz = src->nz;
	dst->s = src->s;
	dst->t = src->t;
}