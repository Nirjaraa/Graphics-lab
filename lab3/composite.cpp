#include <GL/glut.h>
#include <cmath>

struct Point { float x, y; };

 Point A = {50, 50}, B = {150, 50}, C = {100, 150};

 float angle = 0;      
float scaleX = 1.0f, scaleY = 1.0f;  
float shearX = 0.0f;   
float transX = 0.0f, transY = 0.0f;  

int step = 0; 

void drawTriangle(Point A, Point B, Point C) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(A.x, A.y);
        glVertex2f(B.x, B.y);
        glVertex2f(C.x, C.y);
    glEnd();
}

void drawAxes() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
        glVertex2f(-400,0); glVertex2f(400,0);
        glVertex2f(0,-300); glVertex2f(0,300);
    glEnd();
}

Point applyMatrix(Point p, float mat[3][3]) {
    float x = mat[0][0]*p.x + mat[0][1]*p.y + mat[0][2];
    float y = mat[1][0]*p.x + mat[1][1]*p.y + mat[1][2];
    return {x, y};
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    glColor3f(1,1,1);
    drawTriangle(A,B,C);

    // Create matrices
    float theta = angle * 3.14159265f / 180.0f;
    float R[3][3] = {
        { cosf(theta), -sinf(theta), 0 },
        { sinf(theta),  cosf(theta), 0 },
        { 0, 0, 1 }
    };
    float S[3][3] = {
        { scaleX, 0, 0 },
        { 0, scaleY, 0 },
        { 0, 0, 1 }
    };
    float Sh[3][3] = {
        { 1, shearX, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    float T[3][3] = {
        {1, 0, transX},
        {0, 1, transY},
        {0, 0, 1}
    };

    // Multiply: M = T * Sh * S * R
    float temp1[3][3], temp2[3][3], M[3][3];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            temp1[i][j]=0;
            for(int k=0;k<3;k++) temp1[i][j]+=Sh[i][k]*S[k][j];
        }
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            temp2[i][j]=0;
            for(int k=0;k<3;k++) temp2[i][j]+=temp1[i][k]*R[k][j];
        }
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++){
            M[i][j]=0;
            for(int k=0;k<3;k++) M[i][j]+=T[i][k]*temp2[k][j];
        }

    Point A1 = applyMatrix(A,M);
    Point B1 = applyMatrix(B,M);
    Point C1 = applyMatrix(C,M);

    glColor3f(1,0,0);
    drawTriangle(A1,B1,C1);

    glFlush();
}

void timer(int) {
    if(step==0){ // Rotation
        angle += 1;
        if(angle >= 45) { angle = 45; step++; } // stop at 45 degrees
    }
    else if(step==1){ // Scaling
        scaleX += 0.01;
        scaleY += 0.01;
        if(scaleX >= 1.5) { scaleX=1.5; scaleY=1.5; step++; }
    }
    else if(step==2){ // Shearing
        shearX += 0.01;
        if(shearX >= 0.5) { shearX = 0.5; step++; }
    }
    else if(step==3){ // Translation
        transX += 1;
        transY += 0.5;
        if(transX >= 100) { transX = 100; transY = 50; step++; }
    }

    glutPostRedisplay();
    if(step<4) glutTimerFunc(20, timer, 0); // stop timer after all 4
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Sequential Composite Transformation");
    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();gluOrtho2D(-500, 500, -400, 400);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
}
