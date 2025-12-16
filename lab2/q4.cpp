#include <GL/glut.h>
#include <vector>
#include <cmath>
using namespace std;

void DDA(int x1,int y1,int x2,int y2){
    float dx=x2-x1,dy=y2-y1;
    float steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    float Xinc=dx/steps,Yinc=dy/steps;
    float X=x1,Y=y1;
    glBegin(GL_POINTS);
    for(int i=0;i<=steps;i++){
        glVertex2i(round(X),round(Y));
        X+=Xinc;Y+=Yinc;
    }
    glEnd();
}

void LineGraph(vector<int> data,int startX,int startY,int gap){
    for(size_t i=0;i<data.size()-1;i++)
        DDA(startX+i*gap,startY+data[i],startX+(i+1)*gap,startY+data[i+1]);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    vector<int> data={50,100,80,150,120};
    LineGraph(data,50,50,50);
    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("Line Graph");
    glClearColor(0,0,0,1);
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
