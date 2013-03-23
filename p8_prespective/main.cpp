#include <iostream>
#include<stdlib.h>
#include<GL/glut.h>

using namespace std;

GLfloat vertices[][3]= {{-1,-1,-1},{1,-1,-1},{1,1,-1},{-1,1,-1},{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1}};
GLfloat colors[][3]= {{0,0,0},{1,0,0},{1,1,0},{0,1,0},{0,0,1},{1,0,1},{1,1,1},{0,1,1}};

void polygon(int a, int b, int c, int d)
{

	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube()
{
	polygon(0,3,2,1);
	polygon(2,3,7,6);
	polygon(0,4,7,3);
	polygon(1,2,6,5);
	polygon(4,5,6,7);
	polygon(0,1,5,4);
}

static GLfloat theta[]= {0.0,0.0,0.0};
static GLint axis=2;
static GLdouble viewer[]= {0,0,5};

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
	colorcube();
	glFlush();
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
	if(key=='x')    viewer[0]-=1;
	if(key=='X')    viewer[0]+=1;
	if(key=='y')    viewer[1]-=1;
	if(key=='Y')    viewer[1]+=1;
	if(key=='z')    viewer[2]-=1;
	if(key=='Z')    viewer[2]+=1;
	display();
}

void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		axis=0;
	if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		axis=1;
	if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		axis=2;
	theta[axis]+=1.0;
	if(theta[axis]>360.0)
		theta[axis]-=360.0;
	display();
}

void myreshape(int w, int h)
{

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glFrustum(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,2.0,20.0);
	else
		glFrustum(-2.0,2.0,-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,2.0,20.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("Prespective viewing -- Arpith");
	glutReshapeFunc(myreshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
