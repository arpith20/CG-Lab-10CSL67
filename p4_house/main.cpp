#include <iostream>
#include<GL/glut.h>
#include<math.h>

using namespace std;

GLfloat house[3][9]={{100,100,175,250,250,150,150,200,200},
               {100,300,400,300,100,100,150,150,100},
               {1,1,1,1,1,1,1,1,1}};

GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat result[3][9]={{0},{0},{0}};
GLfloat h=100.0;        //pivot points (x-axis)
GLfloat k=100.0;        //pivot points (y-axis)

GLfloat theta;

void multiply()
{
        int i, j, k;
        for(i=0;i<3;i++)
                for(j=0;j<9;j++)
                {
                        result[i][j]=0;
                        for(k=0;k<3;k++)
                                result[i][j]=result[i][j]+rot_mat[i][k]*house[k][j];
                }
}

void rotate()
{
        GLfloat m, n;
        m=-h*(cos(theta)-1)+k*(sin(theta));
        n=-k*(cos(theta)-1)-h*(sin(theta));
        rot_mat[0][0] = cos(theta);
        rot_mat[0][1] = -sin(theta);
        rot_mat[0][2] = m;
        rot_mat[1][0] = sin(theta);
        rot_mat[1][1] = cos(theta);
        rot_mat[1][2] = n;
        rot_mat[2][0] = 0;
        rot_mat[2][1] = 0;
        rot_mat[2][2] = 1;
        multiply();
}

void drawhouse()
{
        int i;
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        for(i=0;i<=4;i++)
                if(i!=2)
                        glVertex2f(house[0][i],house[1][i]);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        for(i=5;i<=8;i++)
                        glVertex2f(house[0][i],house[1][i]);
        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        for(i=1;i<=3;i++)
                        glVertex2f(house[0][i],house[1][i]);
        glEnd();
}

void drawrotatedhouse()
{
        int i;
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        for(i=0;i<=4;i++)
                if(i!=2)
                        glVertex2f(result[0][i],result[1][i]);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        for(i=5;i<=8;i++)
                        glVertex2f(result[0][i],result[1][i]);
        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        for(i=1;i<=3;i++)
                        glVertex2f(result[0][i],result[1][i]);
        glEnd();
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        drawhouse();
        rotate();
        drawrotatedhouse();
        glFlush();
}

void myinit()
{
        glClearColor(1,1,1,1);
        glColor3f(1,0,0);
        glPointSize(1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,499,0,499);
}

int main(int argc, char *argv[])
{
        cout<<"Enter rotation angle: ";
        cin>>theta;
        theta=theta*(3.14/180);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("House Rotate -- Arpith");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

