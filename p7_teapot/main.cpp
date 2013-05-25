#include <iostream>
#include <GL/glut.h>

using namespace std;

GLfloat x=2.3, y=1.3;

void wall(double thickness)
{
        glPushMatrix();
        glTranslated(0.5,0.5*thickness,0.5);
        glScaled(1.0,thickness,1.0);
        glutSolidCube(1.0);
        glPopMatrix();
}

//draw one table leg
void tableleg(double thick, double len)
{
        glPushMatrix();
        glTranslated(0,len/2,0);
        glScaled(thick,len,thick);
        glutSolidCube(1.0);
        glPopMatrix();
}

void table(double topWid,double topThick,double legThick,double legLen)
{
        //draw the table - a top and 4 legs
        //draw the top first
        glPushMatrix();
        glTranslated(0,legLen,0);
        glScaled(topWid,topThick,topWid);
        glutSolidCube(1.0);
        glPopMatrix();
        double dist=0.95*topWid/2.0-legThick/2.0;
        glPushMatrix();
        glTranslated(dist,0,dist);
        tableleg(legThick,legLen);
        glTranslated(0,0,-2*dist);
        tableleg(legThick,legLen);
        glTranslated(-2*dist,0,2*dist);
        tableleg(legThick,legLen);
        glTranslated(0,0,-2*dist);
        tableleg(legThick,legLen);
        glPopMatrix();
}

void displaySolid()
{
        //set proporties for surface material
        GLfloat mat_ambient[]={0.7f,0.7f,0.7f,1.0f};
        GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
        GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
        GLfloat mat_shininess[]={50.0f};
        glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
        glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
        glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

        //set light source properties
        GLfloat lightIntensity[]={0.7f,0.7f,0.7f,1.0f};
        GLfloat lightPosition[]={2.0f,6.0f,3.0f,0.0f};
        glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

        //set the camera
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        double winHt=1.0;        //half-height of window
        glOrtho(-winHt*64/48.0,winHt*64/48.0,-winHt,winHt,0.1,100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(x,y,2.0,0.0,0.25,0.0,0.0,1.0,0.0);

        //start drawing
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslated(0.6,0.38,0.5);
        glRotated(30,0,1,0);
        glutSolidTeapot(0.08);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0.4,0,0.4);
        table(0.6,0.02,0.02,0.3);
        glPopMatrix();

        wall(0.02);

        glPushMatrix();
        glRotated(90,0,0,1);
        wall(0.02);
        glPopMatrix();

        glPushMatrix();
        glRotated(-90,1,0,0);
        wall(0.02);
        glPopMatrix();

        glutPostRedisplay();
        glutSwapBuffers();
        glFlush();
}

void motion(int x1, int y1)
{
        x=x1/100;
        y=y1/100;
}

int main(int argc, char *argv[])
{
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
        glutInitWindowSize(640,480);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Teapot -- Arpith");
        glutDisplayFunc(displaySolid);
        glutMotionFunc(motion);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);
        glClearColor(0.1,0.1,0.1,0.0);
        glViewport(0,0,640,480);
        glutMainLoop();
        return 0;
}
