#include<iostream>
#include<GL/glut.h>
#include<GL/glu.h>

using namespace std;

float xmin,xmax,ymin,ymax,xvmin,xvmax,yvmin,yvmax,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8;
bool cliptest(float p,float q,float* t1,float* t2)
{
	float t=q/p;
	if(p<0.0)
	{
		if(t>*t1)
			*t1=t;
		else if(t>*t2)
			return false;
	}
	else if(p>0.0)
	{
		if(t<*t2)
			*t2=t;
		else if(t<*t1)
			return false;
	}
	else if(p==0.0)
	{
		if(q<0.0)
			return false;
	}
	return true;
}
void liang(float x0,float y0,float x1,float y1)
{
	float dx=x1-x0,dy=y1-y0,te=0.0,t1=1.0;
	if(cliptest(-dx,x0-xmin,&te,&t1))
		if(cliptest(dx,xmax-x0,&te,&t1))
			if(cliptest(-dy,y0-ymin,&te,&t1))
				if(cliptest(dy,ymax-y0,&te,&t1))
				{
					if(t1<1.0)
					{
						x1=x0+t1*dx;
						y1=y0+t1*dy;
					}
					if(te>0.0)
					{
						x0=x0+te*dx;
						y0=y0+te*dy;
					}
					float sx=(xvmax-xvmin)/(xmax-xmin);
					float sy=(yvmax-yvmin)/(ymax-ymin);
					float vx0=xvmin+(x0-xmin)*sx;
					float vx1=xvmin+(x1-xmin)*sx;
					float vy0=yvmin+(y0-ymin)*sy;
					float vy1=yvmin+(y1-ymin)*sy;
					glColor3f(1,0,0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xvmin,yvmin);
					glVertex2f(xvmin,yvmax);
					glVertex2f(xvmax,yvmax);
					glVertex2f(xvmax,yvmin);
					glEnd();
					glColor3f(0,1,0);
					glBegin(GL_LINES);
					glVertex2f(vx0,vy0);
					glVertex2f(vx1,vy1);
					glEnd();
				}
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);
	glVertex2f(x5,y5);
	glVertex2f(x6,y6);
	glVertex2f(x7,y7);
	glVertex2f(x8,y8);
	glEnd();
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmin,ymax);
	glVertex2f(xmax,ymax);
	glVertex2f(xmax,ymin);
	glEnd();
	glFlush();
	liang(x1,y1,x2,y2);
	liang(x3,y3,x4,y4);
	liang(x5,y5,x6,y6);
	liang(x7,y7,x8,y8);
	glFlush();
}
void init()
{
	glClearColor(1,1,1,1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,499,0,499);
}
int main(int argc,char** argv)
{
	cout<<"min window coord:";
	cin>>xmin>>ymin;
	cout<<"max window coord:";
	cin>>xmax>>ymax;
	cout<<"min viewport window coord:";
	cin>>xvmin>>yvmin;
	cout<<"max viewport window coord:";
	cin>>xvmax>>yvmax;
	cout<<"line co ord for 1st line:";
	cin>>x1>>y1>>x2>>y2;
	cout<<"line co ord for 2nd line:";
	cin>>x3>>y3>>x4>>y4;
	cout<<"line co ord for 3rd line:";
	cin>>x5>>y5>>x6>>y6;
	cout<<"line co ord for 4th line:";
	cin>>x7>>y7>>x8>>y8;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("liang");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
