#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<GL/glu.h>
#include<math.h>
float theta;
float h=150,k=150;
float house[3][9]= {{150.0,150.0,225.0,300.0,300.0,200.0,200.0,250.0,250.0},{150.0,250.0,300.0,250.0,150.0,150.0,200.0,200.0,150.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}};
float rot[3][3]= {{0},{0},{0}};
float result[3][9]= {{0},{0},{0}};
void drawhouse()
{
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<5; i++)
	{
		if(i!=2)
			glVertex2f(house[0][i],house[1][i]);
	}
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	for(int i=5; i<9; i++)
		glVertex2f(house[0][i],house[1][i]);

	glEnd();

	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i=1; i<4; i++)
		glVertex2f(house[0][i],house[1][i]);

	glEnd();
}

void drawrotatedhouse()
{
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<5; i++)
	{
		if(i!=2)
			glVertex2f(result[0][i],result[1][i]);

	}
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	for(int i=5; i<9; i++)
		glVertex2f(result[0][i],result[1][i]);
	glEnd();

	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(int i=1; i<4; i++)
		glVertex2f(result[0][i],result[1][i]);

	glEnd();
}
void multiply()
{
	int i,j,k;
	for(i=0; i<3; i++)
	{
		for(j=0; j<9; j++)
		{
			result[i][j]=0;
			for(k=0; k<3; k++)
				result[i][j]+=rot[i][k]*house[k][j];
		}
	}
}
void rotate()
{
	float m,n;
	m=-h*(cos(theta)-1)+k*(sin(theta));
	n=-k*(cos(theta)-1)-h*(sin(theta));
	rot[0][0]=cos(theta);
	rot[0][1]=-sin(theta);
	rot[0][2]=m;
	rot[1][0]=sin(theta);
	rot[1][1]=cos(theta);
	rot[1][2]=n;
	rot[2][0]=0;
	rot[2][1]=0;
	rot[2][2]=1;
	multiply();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawhouse();
	rotate();
	drawrotatedhouse();
	glFlush();
}
void init()
{
	glClearColor(1,1,1,1);
//glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,499,0,499);
}
int main(int argc,char** argv)
{
	cout<<"angle:";
	cin>>theta;
	theta=theta*(3.14/180);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("house");
	init();
//glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
