#include <iostream>
#include <GL/glut.h>

using namespace std;

float theta=180;

void house()
{
        //draw roof
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0,100);
        glVertex2f(100,100);
        glVertex2f(50,150);
        glEnd();
        //draw square
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(0,0);
        glVertex2f(100,0);
        glVertex2f(100,100);
        glVertex2f(0,100);
        glEnd();
        //draw door
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(40,0);
        glVertex2f(60,0);
        glVertex2f(60,40);
        glVertex2f(40,40);
        glEnd();
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(200,200,0);
        house();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(200,200,0);
        glRotatef(theta,0,0,1);
        house();
        glPopMatrix();

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
        cout<<"enter angle: ";cin>>theta;
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(500,500);
        glutCreateWindow("house -- Arpith");
        init();
        glutDisplayFunc(display);
        glutMainLoop();
        return 0;
}
