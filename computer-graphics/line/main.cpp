#include <iostream>
#include"graphics.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//Ax + By + C = 0;
//A = -deltaY  B = deltaX  
void middlePoint(int x1, int y1, int x2, int y2)
{

	int idxX, idxY, d0, dUp, dDown, A, B;
	A = x1 - x2;
	B = y2 - y1;
	d0 = 2 * A + B;
	dUp = 2 * (A + B);
	dDown = 2 * A;
	idxY = y1;
	
	for(idxX = x1; idxX <= x2; idxX++)
	{
		putpixel(idxX, idxY, GREEN);
		if(d0 < 0)
		{
			idxY++;
			d0 += dUp;	
		}	
		else
		{
			d0 += dDown;
		}
	} 
}


void ddaLine(int x1, int y1, int x2, int y2)
{
	int idxX;
	float k, dy;
	k = 1.0 * (y2 - y1) / (x2 - x1);
	dy = y1;
	
	for(idxX = x1; idxX <= x2; idxX++)
	{
		putpixel(idxX, (int)(dy + 0.5), RED);
		dy = dy + k;
	}
	
}

void bresenham(int x1, int y1, int x2, int y2)
{
	int idxX, tmpY, p, dy, dx;
	dy = y2 - y1;
	dx = x2 - x1;
	p = 2 * dy - dx;
	tmpY = y1;
	
	for(idxX = x1; idxX <= x2; idxX++)
	{
		putpixel(idxX, tmpY, BLUE);

		if(p > 0)
		{
			tmpY++;
			p += 2 * (dy - dx);
		}
		else
		{
			p += 2 * dy;
		}
	}
}
 
int main(int argc, char** argv) {
	initgraph(640, 480);
	//outtextxy(60, 100, "hello world");
	//circle(100, 100, 50);
	middlePoint(200, 160, 400, 400);
	ddaLine(0, 0, 50, 20);
	bresenham(20, 20, 200, 180);
	ege::getch();
	closegraph();
	return 0;
}
