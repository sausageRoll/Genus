#include "LagranzhRoadMaker.h"
#include "CubicSplineRoadMaker.h"
#include "CanonicalRoadMaker.h"

#include <windows.h>
#include <time.h>
#include <iostream>
#include <memory>
#include <glut.h>

double* X = new double[640];
double* Y = new double[640];
int N = 0;
int flag = -1;

typedef std :: shared_ptr<CubicSplineRoadMaker> CubicSplineRoadMakerPointer;
CubicSplineRoadMakerPointer cS(CubicSplineRoadMakerPointer(new CubicSplineRoadMaker(xStart,yStart)));

void Init(void)
{
	glClearColor(0.0,1.0,0.0,0.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,640,0.0,480,-1.0,1.0);
};



void pole()
{
	glClear(GL_COLOR_BUFFER_BIT);

		glColor3d(0.2,0.2,0.2);
		glBegin(GL_POINTS);
			for (double t = 0.0; t < 640.0; t += 0.1)
				glVertex2d(t,cS->f(t));
		glEnd();
		glColor3d(0.5,0.5,0.5);
		//cS->fastDraw();
	
	glutSwapBuffers();

	//Sleep(500);
};

void make(int x,int y)
{
	y = 480 - y;
	if (flag == 0)
	{
		if (N == 0) 
		{
			X[N] = x;
			Y[N++] = y;
		} else if ((abs(X[N-1] - x) >= 1))
		{
			X[N] = x;
			Y[N++] = y;
			cS->pushNewPoint(x,y);
		}
	}
}

void control(int button, int state,
                                int x, int y)
{
	if (flag <= 0)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			if (state == GLUT_DOWN)
				flag = 0;
			else
			{
				flag = 1;
				/*cS = CanonicalRoadMakerPointer(new CanonicalRoadMaker(X,Y,N));
				cS->makeSpline();*/
			}
		}
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,200);
	glutCreateWindow("CanonicalRoadMaker");
	Init();
	glutDisplayFunc(pole);
	glutMotionFunc(make);
	glutMouseFunc(control);
	glutIdleFunc(pole);
	glutMainLoop();
	return 0;
};