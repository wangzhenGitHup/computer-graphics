#include <iostream>
#include"graphics.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>


#define N 100000
#define Min -99999999
int n;         //点的个数
int right;     //图像的右边界
 
struct point   //点的坐标
{
    int x;
    int y;
}point[N];
 
void init()  //初始化，点的坐标
{
    int i;
    printf("请输入点的个数: ");
    scanf("%d",&n);
    right=Min;
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&point[i].x,&point[i].y);
        if(point[i].x>right)  //得到右边界
			right=point[i].x;
    }
    point[n].x=point[0].x;    //首尾相连，构成封闭图形
    point[n].y=point[0].y;
}
 
void display()          //绘制该多边形的轮廓
{
    int i;
    setbkcolor(WHITE);  
    cleardevice();
    setcolor(RED);
    
    for(i=0;i<n;i++)    //画边界线
        line(point[i].x,point[i].y,point[i+1].x,point[i+1].y);
}
void fill()            //边缘填充算法
{
    int x0,y0,x1,y1,i;
    int dx,dy,eps1,k;
    int p,q;
    int flag;
    int temp;
    float x,y,xIncre,yIncre;
    for(i=0;i<n;i++)
    {
        //如果线段是水平线或者是右边边界，只画线，不做处理
        if(point[i+1].y==point[i].y||(right==point[i+1].x&&right==point[i].x))
            line(point[i].x,point[i].y,point[i+1].x,point[i+1].y);
        else
		{
            //初始化各个参数
            x=point[i+1].x;
            y=point[i+1].y;
            dx=point[i].x-point[i+1].x;
            dy=point[i].y-point[i+1].y;
 
            //扫描线的范围
            eps1=abs(dy);
 
            xIncre=(float)dx/(float)eps1;
            yIncre=(float)dy/(float)eps1;
            //找线段上的点
            for(k=0;k<=eps1;k++)
            {
				p=(int)(x+0.5);
				q=(int)(y+0.5);
                //扫描线上取补
				for(int j=p;j<=right;j++)
			    {
                  //如果当前点为白色，就填充红色
					if(getpixel(j,q)==WHITE)
						putpixel(j,q,RED);
                  //否则就填充白色
					else
						putpixel(j,q,WHITE);
				}
				x+=xIncre;
				y+=yIncre;
			}
        }
    }
}

int main()
{
 
    init();
    initgraph(800,700);
    display();
    fill();
    getch();
    closegraph();
    return 0;
}

