#include <windows.h>
#include <gl/Gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

class WcPt2D
{
public:
	WcPt2D() : x_(0), y_(0){}

	WcPt2D(GLfloat x, GLfloat y) : x_(x), y_(y){}

	GLfloat x_, y_;
};

void setPixel(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void lineBres(int x0, int y0, int xEnd, int yEnd)
{
	int dx = abs(xEnd - x0), dy = abs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;

	if (x0 > xEnd)
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else
	{
		x = x0;
		y = y0;
	}

	setPixel(x, y);

	while (x < xEnd)
	{
		x++;
		if (p < 0)
		{
			p += twoDy;
		}
		else
		{
			y++;
			p += twoDyMinusDx;
		}

		setPixel(x, y);
	}
}

GLint roundInt(const GLfloat a)
{
	return GLint(a + 0.5);
}

const GLint winLeftBitCode = 0x1;
const GLint winRightBitCode = 0x2;
const GLint winBottomBitCode = 0x4;
const GLint winTopBitCode = 0x8;

GLint inside(GLint code)
{
	return GLint(!code);
}

GLint reject(GLint code1, GLint code2)
{
	return GLint(code1 & code2);
}

GLint accpet(GLint code1, GLint code2)
{
	return GLint(!(code1 | code2));
}

GLubyte encode(WcPt2D pt, WcPt2D winMin, WcPt2D winMax)
{
	GLubyte code = 0x00;
	if (pt.x_ < winMin.x_)
	{
		code = code | winLeftBitCode;
	}

	if (pt.x_ > winMax.x_)
	{
		code = code | winRightBitCode;
	}

	if (pt.y_ < winMin.y_)
	{
		code = code | winBottomBitCode;
	}

	if (pt.y_ > winMax.y_)
	{
		code = code | winTopBitCode;
	}

	return code;
}


void swapPts(WcPt2D* p1, WcPt2D* p2)
{
	WcPt2D tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void swapCodes(GLubyte* c1, GLubyte* c2)
{
	GLubyte tmp;
	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void lineClipCohSuth(WcPt2D winMin, WcPt2D winMax, WcPt2D p1, WcPt2D p2)
{
	GLubyte code1, code2;
	GLint done = false, plotLine = false;
	GLfloat m;

	while (!done)
	{
		code1 = encode(p1, winMin, winMax);
		code2 = encode(p2, winMin, winMax);
		if (accpet(code1, code2))
		{
			done = true;
			plotLine = true;
		}
		else
		{
			if (reject(code1, code2))
			{
				done = true;
			}
			else
			{
				if (inside(code1))
				{
					swapPts(&p1, &p2);
					swapCodes(&code1, &code2);
				}

				if (p2.x_ != p1.x_)
				{
					m = (p2.y_ - p1.y_) / (p2.x_ - p1.x_);
				}

				if (code1 & winLeftBitCode)
				{
					p1.y_ += (winMin.x_ - p1.x_) * m;
					p1.x_ = winMin.x_;
				}
				else
				{
					if (code1 & winRightBitCode)
					{
						p1.y_ += (winMax.x_ - p1.x_) * m;
						p1.x_ = winMax.x_;
					}
					else
					{
						if (code1 & winBottomBitCode)
						{
							if (p2.x_ != p1.x_)
							{
								p1.x_ += (winMin.y_ - p1.y_) / m;
							}

							p1.y_ = winMin.y_;
						}
						else
						{
							if (code1 & winTopBitCode)
							{
								if (p2.x_ != p1.x_)
								{
									p1.x_ += (winMax.y_ - p1.y_) / m;
								}
								p1.y_ = winMax.y_;
							}
						}
					}
				}
			}
		}
	}

	if (plotLine)
	{
		lineBres(roundInt(p1.x_), roundInt(p1.y_), 
			roundInt(p2.x_), roundInt(p2.y_));
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

void drawRect()
{


	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(2.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2i(10, 10);
	glVertex2i(10, 300);
	glVertex2i(300, 300);
	glVertex2i(300, 10);
	glEnd();

	glFlush();
}

void myDisplay()
{
	WcPt2D winMin(10, 10);
	WcPt2D winMax(300, 300);
	WcPt2D p1(15, 15);
	WcPt2D p2(500, 250);

	glClear(GL_COLOR_BUFFER_BIT);
	drawRect();
	glColor3f(1.0f, 0.0f, 0.0f);
	lineClipCohSuth(winMin, winMax, p1, p2);
	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Cohen-Sutherland");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}