#include<stdio.h>
#include<iostream>
#include<GL/glut.h>

using namespace std;

#define outcode int

double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
double x00,y00,x10,y10;
double x01,y01,x11,y11;
double x02,y02,x12,y12;
double x03,y03,x13,y13;
const int RIGHT=8;
const int LEFT=2;
const int TOP=4;
const int BOTTOM=1;

outcode ComputeOutCode(double x, double y);

void CohenSutherland(double x0, double y0, double x1, double y1)
{
	outcode outcode0, outcode1, outcodeOut;
	bool accept=false, done=false;
	outcode0=ComputeOutCode(x0,y0);
	outcode1=ComputeOutCode(x1,y1);
	do
	{
		if(!(outcode0|outcode1))
		{
			accept=true;
			done=true;
		}
		else if(outcode0&outcode1)
			done=true;
		else
		{
			double x, y;
			outcodeOut=outcode0?outcode0:outcode1;
			if(outcodeOut&TOP)
			{
				x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
				y=ymax;
			}
			else if(outcodeOut&BOTTOM)
			{
				x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
				y=ymin;
			}
			else if(outcodeOut&RIGHT)
			{
				y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
				x=xmax;
			}
			else
			{
				y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
				x=xmin;
			}
			if(outcodeOut==outcode0)
			{
				x0=x;
				y0=y;
				outcode0=ComputeOutCode(x0,y0);
			}
			else
			{
				x1=x;
				y1=y;
				outcode1=ComputeOutCode(x1,y1);
			}
		}
	} while(!done);
	if(accept)
	{
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-ymin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-ymin)*sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
		glVertex2d(vx0,vy0);
		glVertex2d(vx1,vy1);
		glEnd();
	}
}

outcode ComputeOutCode(double x, double y)
{
	outcode code=0;
	if(y>ymax)
		code=TOP;
	else if(y<ymin)
		code=BOTTOM;
	if(x>xmax)
		code=RIGHT;
	else if(x<xmin)
		code=LEFT;
	return code;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(x00,y00);
	glVertex2d(x10,y10);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(x01,y01);
	glVertex2d(x11,y11);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(x02,y02);
	glVertex2d(x12,y12);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(x03,y03);
	glVertex2d(x13,y13);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();
	CohenSutherland(x00,y00,x10,y10);
	CohenSutherland(x01,y01,x11,y11);
	CohenSutherland(x02,y02,x12,y12);
	CohenSutherland(x03,y03,x13,y13);
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}

int main(int argc, char* argv[])
{
	cout<<"Enter the endpoints of the line1:\n";
	cin>>x00>>y00>>x10>>y10;
	cout<<"Enter the endpoints of the line2:\n";
	cin>>x01>>y01>>x11>>y11;
	cout<<"Enter the endpoints of the line3:\n";
	cin>>x02>>y02>>x12>>y12;
	cout<<"Enter the endpoints of the line4:\n";
	cin>>x03>>y03>>x13>>y13;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cohen-Sutherland Line Clipping -- Arpith");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
