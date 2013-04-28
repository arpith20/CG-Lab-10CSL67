#include <iostream>
#include <GL/glut.h>
#define BLACK 0

using namespace std;

float x1=200,x2=300,x3=250,x4=200,y1=100,y2=100,y3=250,y4=350;

void edgedetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
        float mx,x,temp;
        int i;
        if((y2-y1)<0)
        {
                temp=y1; y1=y2; y2=temp;
                temp=x1; x1=x2; x2=temp;
        }
        if((y2-y1)!=0)
                mx=(x2-x1)/(y2-y1);
        else
                mx=x2-x1;
        x=x1;
        for(i=y1;i<=y2;i++)
        {
                if(x<(float)le[i])
                        le[i]=(int)x;
                if(x>(float)re[i])
                        re[i]=(int)x;
                x+=mx;
        }
}

void draw_pixel(int x, int y, int value)
{
        glColor3f(1,0,0);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
}

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
        int le[500], re[500];
        int i,y;
        for(i=0;i<500;i++)
        {
                le[i]=500;
                re[i]=0;
        }
        edgedetect(x1,y1,x2,y2,le,re);
        edgedetect(x2,y2,x3,y3,le,re);
        edgedetect(x3,y3,x4,y4,le,re);
        edgedetect(x4,y4,x1,y1,le,re);
        for(y=0;y<500;y++)
        {
                if(le[y]<=re[y])
                        for(i=(int)le[y];i<(int)re[y];i++)
                                draw_pixel(i,y,BLACK);
        }
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glVertex2f(x3,y3);
        glVertex2f(x4,y4);
        glEnd();
        scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
        glFlush();
}

void myinit()
{
        glClearColor(1,1,1,1);
        glColor3f(1,0,0);
        glPointSize(1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,499,0,499);
}

void getVal()
{
        cout<<"Enter enter point 1: ";
        cin>>x1>>y1;
        cout<<"Enter enter point 2: ";
        cin>>x2>>y2;
        cout<<"Enter enter point 3: ";
        cin>>x3>>y3;
        cout<<"Enter enter point 4: ";
        cin>>x4>>y4;
}

int main(int argc, char *argv[])
{
        getVal();
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Scan-Line Algorithm -- Arpith");
        glutDisplayFunc(display);
        myinit();
        glutMainLoop();
        return 0;
}
