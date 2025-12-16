#include <GL/glut.h>
#include <cmath>
using namespace std;

void MidpointCircle(int xc,int yc,int r) {
    int x=0,y=r;
    int p=1-r;
    glBegin(GL_POINTS);
    while(x<=y){
        glVertex2i(xc+x,yc+y);
        glVertex2i(xc-x,yc+y);
        glVertex2i(xc+x,yc-y);
        glVertex2i(xc-x,yc-y);
        glVertex2i(xc+y,yc+x);
        glVertex2i(xc-y,yc+x);
        glVertex2i(xc+y,yc-x);
        glVertex2i(xc-y,yc-x);
        x++;
        if(p<0) p += 2*x +1;
        else {y--; p += 2*(x-y)+1;}
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    MidpointCircle(250,250,100);
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Midpoint Circle Drawing");
    glClearColor(0,0,0,1);
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
