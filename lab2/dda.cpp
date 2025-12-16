#include <GL/glut.h>
#include <cmath>
using namespace std;

void DDA(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1, dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float Xinc = dx / steps, Yinc = dy / steps;
    float X = x1, Y = y1;
    glBegin(GL_POINTS);
    for(int i = 0; i <= steps; i++) {
        glVertex2i(round(X), round(Y));
        X += Xinc; Y += Yinc;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    DDA(50,50,300,200);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutCreateWindow("DDA Line Drawing");
    glClearColor(0,0,0,1);
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
