#include <iostream>
#include<stdlib.h>
#include<GL/glut.h>

using namespace std;

GLfloat x0, y0;
GLfloat dx, dy;
GLfloat maxx, maxy;
GLfloat x[100]={0.0},y[100]={0.0};
GLint i, j;

void init()
{
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3f(1.0,0.0,0.0);
        glPointSize(5.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0,499.0,0.0,499.0);
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0,0.0,1.0);
        for(i=0;i<maxx;i++)
                x[i]=x0+i*dx;
        for(j=0;j<maxy;j++)
                y[j]=y0+j*dy;
        glColor3f(0.0,0.0,1.0);
        for(i=0;i<maxx-1;i++)
        {
                for(j=0;j<maxy-1;j++)
                {
                        glBegin(GL_LINE_LOOP);
                        glVertex2f(x[i],y[j]);
                        glVertex2f(x[i],y[j+1]);
                        glVertex2f(x[i+1],y[j+1]);
                        glVertex2f(x[i+1],y[j]);
                        glEnd();
                }
                glFlush();
        }
}

void getval()
{
        cout<<"Enter initial points:\n";
        cout<<"x0: ";
        cin>>x0;
        cout<<"y0: ";
        cin>>y0;
        cout<<"Enter displacement b/w two lines:\n";
        cout<<"dx: ";
        cin>>dx;
        cout<<"dy: ";
        cin>>dy;
        cout<<"Enter maximum values:\n";
        cout<<"maxx: ";
        cin>>maxx;
        cout<<"maxy: ";
        cin>>maxy;
}

int main(int argc, char *argv[])
{
        getval();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Mesh");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
}
