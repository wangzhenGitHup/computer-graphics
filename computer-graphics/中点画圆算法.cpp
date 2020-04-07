#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

class ScreenPt
{
public:
	ScreenPt() : m_x(0), m_y(0){}

	void setCoords(GLint x, GLint y)
	{
		m_x = x;
		m_y = y;
	}

	GLint getX()const
	{
		return m_x;
	}

	GLint getY()const
	{
		return m_y;
	}

	void incrementX()
	{
		m_x++;
	}

	void decrementry()
	{
		m_y--;
	}

private:
	GLint m_x, m_y;
};

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void circlePlotPoints(GLint x, GLint y, ScreenPt pt)
{
	setPixel(x + pt.getX(), y + pt.getY());
	setPixel(x - pt.getX(), y + pt.getY());
	setPixel(x + pt.getX(), y - pt.getY());

	setPixel(x - pt.getX(), y - pt.getY());
	setPixel(x + pt.getY(), y + pt.getX());
	setPixel(x - pt.getY(), y + pt.getX());

	setPixel(x + pt.getY(), y - pt.getX());
	setPixel(x - pt.getY(), y - pt.getX());
}

void circleMiddlePoint(GLint x, GLint y, GLint r)
{
	ScreenPt circlePt;
	GLint p = 1 - r;
	circlePt.setCoords(0, r);

	circlePlotPoints(x, y, circlePt);
	while (circlePt.getX() < circlePt.getY())
	{
		circlePt.incrementX();
		if (p < 0)
		{
			p += 2 * circlePt.getX() + 1;
		}
		else
		{
			circlePt.decrementry();
			p += 2 * (circlePt.getX() - circlePt.getY()) + 1;
		}

		circlePlotPoints(x, y, circlePt);
	}
}



void myInit()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(3.0f);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}


void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	circleMiddlePoint(150, 150, 100);
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Middle Draw Circle");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}