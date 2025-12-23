#include <GL/glut.h>
#include <vector>
#include <cmath>

struct Point { float x, y; };

void drawAxes() {
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
        glVertex2f(-400,0); glVertex2f(400,0);
        glVertex2f(0,-300); glVertex2f(0,300);
    glEnd();
}

void drawTriangle(const std::vector<Point>& pts){
    glBegin(GL_LINE_LOOP);
        for(auto p: pts) glVertex2f(p.x,p.y);
    glEnd();
}

std::vector<float> multiplyMatrixVector(float mat[3][3], std::vector<float> vec){
    std::vector<float> res(3,0.0f);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            res[i]+=mat[i][j]*vec[j];
    return res;
}

std::vector<Point> applyTransform(const std::vector<Point>& pts, float mat[3][3]){
    std::vector<Point> res;
    for(auto p: pts){
        std::vector<float> vec = {p.x,p.y,1};
        std::vector<float> t = multiplyMatrixVector(mat,vec);
        res.push_back({t[0],t[1]});
    }
    return res;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    std::vector<Point> tri = {{50,50},{150,50},{100,150}};
    glColor3f(1,1,1); drawTriangle(tri); // Original

    // Rotation 45 degrees
    float rad = 45*3.14159265f/180.0f;
    float R[3][3] = {
        {cosf(rad),-sinf(rad),0},
        {sinf(rad),cosf(rad),0},
        {0,0,1}
    };

    std::vector<Point> rotated = applyTransform(tri,R);
    glColor3f(1,0,0); drawTriangle(rotated);

    glFlush();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("2D Rotation (Matrix)");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluOrtho2D(-400,400,-300,300);
    glutDisplayFunc(display);
    glutMainLoop();
}
