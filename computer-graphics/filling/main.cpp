#include <iostream>
#include"graphics.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>


#define N 100000
#define Min -99999999
int n;         //��ĸ���
int right;     //ͼ����ұ߽�
 
struct point   //�������
{
    int x;
    int y;
}point[N];
 
void init()  //��ʼ�����������
{
    int i;
    printf("�������ĸ���: ");
    scanf("%d",&n);
    right=Min;
    for(i=0;i<n;i++)
    {
        scanf("%d %d",&point[i].x,&point[i].y);
        if(point[i].x>right)  //�õ��ұ߽�
			right=point[i].x;
    }
    point[n].x=point[0].x;    //��β���������ɷ��ͼ��
    point[n].y=point[0].y;
}
 
void display()          //���Ƹö���ε�����
{
    int i;
    setbkcolor(WHITE);  
    cleardevice();
    setcolor(RED);
    
    for(i=0;i<n;i++)    //���߽���
        line(point[i].x,point[i].y,point[i+1].x,point[i+1].y);
}
void fill()            //��Ե����㷨
{
    int x0,y0,x1,y1,i;
    int dx,dy,eps1,k;
    int p,q;
    int flag;
    int temp;
    float x,y,xIncre,yIncre;
    for(i=0;i<n;i++)
    {
        //����߶���ˮƽ�߻������ұ߽߱磬ֻ���ߣ���������
        if(point[i+1].y==point[i].y||(right==point[i+1].x&&right==point[i].x))
            line(point[i].x,point[i].y,point[i+1].x,point[i+1].y);
        else
		{
            //��ʼ����������
            x=point[i+1].x;
            y=point[i+1].y;
            dx=point[i].x-point[i+1].x;
            dy=point[i].y-point[i+1].y;
 
            //ɨ���ߵķ�Χ
            eps1=abs(dy);
 
            xIncre=(float)dx/(float)eps1;
            yIncre=(float)dy/(float)eps1;
            //���߶��ϵĵ�
            for(k=0;k<=eps1;k++)
            {
				p=(int)(x+0.5);
				q=(int)(y+0.5);
                //ɨ������ȡ��
				for(int j=p;j<=right;j++)
			    {
                  //�����ǰ��Ϊ��ɫ��������ɫ
					if(getpixel(j,q)==WHITE)
						putpixel(j,q,RED);
                  //���������ɫ
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

