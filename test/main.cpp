#include<iostream>
using namespace std;
#include<GL/glut.h>
#include<GL/glu.h>
float n,xc,yc,r,x1,y1,x2,y2;
void pix(float x,float y)
{
glColor3f(1,0,1);
glBegin(GL_POINTS);
glVertex2f(x,y);
glEnd();
glFlush();
}
void plotpixel(float h,float k,float x,float y)
{
pix(x+h,y+k);
pix(-x+h,y+k);
pix(x+h,-y+k);
pix(-x+h,-y+k);
pix(y+h,x+k);
pix(-y+h,x+k);
pix(y+h,-x+k);
pix(-y+h,-x+k);
}
void circle(GLfloat h,GLfloat k,GLfloat r)
{
float d=1-r,x=0,y=r;
while(y>x)
{
plotpixel(h,k,x,y);
if(d<0) d+=2*x+3;
else
{
d+=2*(x-y)+5;
--y;
}
++x;
}
plotpixel(h,k,x,y);
}
void cylin_draw()
{
for(int i=0;i<n;i+=2)
circle(xc,yc+i,r);
}
void piped(float x1,float y1,float x2,float y2)
{
glColor3f(1,0,0);
glBegin(GL_LINE_LOOP);
glVertex2f(x1,y1);
glVertex2f(x1,y2);
glVertex2f(x2,y2);
glVertex2f(x2,y1);
glEnd();
glFlush();
}
void piped_draw()
{
for(int i=0;i<n;i+=2)
piped(x1+i,y1+i,x2+i,y2+i);
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0);
cylin_draw();
piped_draw();
glFlush();
}
void init()
{
glClearColor(1,1,1,1);
gluOrtho2D(0,499,0,499);
}
int main(int argc,char**argv)
{
cout<<"for cylinder:";
cout<<"n:";
cin>>n;
cout<<"xc yc :";
cin>>xc>>yc;
cout<<"R:";
cin>>r;
cout<<"for piped:";
cin>>x1>>y1;
cin>>x2>>y2;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutCreateWindow("cylinpip");
glutDisplayFunc(display);
init();
glutMainLoop();
return 0;
}
