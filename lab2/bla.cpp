#include <GL/glut.h>
#include <cmath>
using namespace std;

// Bresenham for |m| < 1
void BresenhamLow(int x0,int y0,int x1,int y1){
    int dx=x1-x0;
    int dy=y1-y0;
    int yi=1;
    if(dy<0){ yi=-1; dy=-dy; }
    int D=2*dy - dx;
    int y=y0;
    glBegin(GL_POINTS);
    for(int x=x0;x<=x1;x++){
        glVertex2i(x,y);
        if(D>0){ y+=yi; D-=2*dx; }
        D+=2*dy;
    }
    glEnd();
}

// Bresenham for |m| >= 1
void BresenhamHigh(int x0,int y0,int x1,int y1){
    int dx=x1-x0;
    int dy=y1-y0;
    int xi=1;
    if(dx<0){ xi=-1; dx=-dx; }
    int D=2*dx - dy;
    int x=x0;
    glBegin(GL_POINTS);
    for(int y=y0;y<=y1;y++){
        glVertex2i(x,y);
        if(D>0){ x+=xi; D-=2*dy; }
        D+=2*dx;
    }
    glEnd();
}

// Dispatcher to choose correct slope
void BresenhamLine(int x0,int y0,int x1,int y1){
    if(abs(y1-y0)<abs(x1-x0)){
        if(x0>x1) BresenhamLow(x1,y1,x0,y0);
        else BresenhamLow(x0,y0,x1,y1);
    } else {
        if(y0>y1) BresenhamHigh(x1,y1,x0,y0);
        else BresenhamHigh(x0,y0,x1,y1);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);

    // Gentle slope |m|<1
    BresenhamLine(50,50,300,100);

    // Steep slope |m|>=1
    BresenhamLine(100,50,150,300);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenham Line Algorithm");
    glClearColor(0,0,0,1);
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
