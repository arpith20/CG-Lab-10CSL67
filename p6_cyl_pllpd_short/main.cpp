#include <iostream>
#include <GL/glut.h>
#include<math.h>

using namespace std;

void draw_circle(GLfloat radius, GLfloat x, GLfloat y)
{
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        for(int i=0;i<=360;i++)
        {
                float rad=i*3.14159/180;
                glVertex2f(cos(rad)*radius+x,sin(rad)*radius+y);
        }
        glEnd();
}

void draw_rect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x2,y1);
        glVertex2f(x2,y2);
        glVertex2f(x1,y2);
        glEnd();
}

void cylinder()
{
        float radius=50,x=100,y=230;
        for(int i=0;i<50;i+=5)
                draw_circle(radius,x,y+i);
}

void parallopiped()
{
        GLfloat x1=300,y1=200,x2=400,y2=300;
        for(int i=0;i<50;i+=5)
                draw_rect(x1+i,y1+i,x2+i,y2+i);
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        cylinder();
        parallopiped();
        glFlush();
}

void init()
{
        glClearColor(1,1,1,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,499,0,499);
}

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(500,500);
        glutCreateWindow("c&p -- Arpith");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
}
