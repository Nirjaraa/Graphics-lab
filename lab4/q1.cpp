#include <GL/glut.h>
using namespace std;

float xmin=50,ymin=50,xmax=300,ymax=300;
bool clipped=false;

const int LEFT=1, RIGHT=2, BOTTOM=4, TOP=8;

int code(float x,float y){
    int c=0;
    if(x<xmin) c|=LEFT;
    if(x>xmax) c|=RIGHT;
    if(y<ymin) c|=BOTTOM;
    if(y>ymax) c|=TOP;
    return c;
}

bool cohen(float &x1,float &y1,float &x2,float &y2){
    int c1=code(x1,y1), c2=code(x2,y2);
    while(true){
        if((c1|c2)==0) return true;
        if(c1&c2) return false;
        float x,y;
        int out=c1?c1:c2;
        if(out&TOP){x=x1+(x2-x1)*(ymax-y1)/(y2-y1);y=ymax;}
        else if(out&BOTTOM){x=x1+(x2-x1)*(ymin-y1)/(y2-y1);y=ymin;}
        else if(out&RIGHT){y=y1+(y2-y1)*(xmax-x1)/(x2-x1);x=xmax;}
        else {y=y1+(y2-y1)*(xmin-x1)/(x2-x1);x=xmin;}
        if(out==c1){x1=x;y1=y;c1=code(x1,y1);}
        else {x2=x;y2=y;c2=code(x2,y2);}
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Window
    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();

    float x1=20,y1=20,x2=350,y2=350;

    if(!clipped){
        // BEFORE
        glColor3f(0.6,0.6,0.6);
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
        glEnd();
    } else {
        // AFTER (only clipped)
        if(cohen(x1,y1,x2,y2)){
            glColor3f(1,0,0);
            glBegin(GL_LINES);
            glVertex2f(x1,y1);
            glVertex2f(x2,y2);
            glEnd();
        }
    }

    glFlush();
}

void timer(int){
    clipped=true;
    glutPostRedisplay();
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cohen-Sutherland Clean Animation");
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutTimerFunc(2000,timer,0);
    glutMainLoop();
}
