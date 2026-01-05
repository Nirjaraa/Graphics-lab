#include <GL/glut.h>
using namespace std;

 float xmin = 50, ymin = 50, xmax = 300, ymax = 300;

 bool clipped = false;

 bool liangBarsky(float x1, float y1, float x2, float y2,
                 float &cx1, float &cy1, float &cx2, float &cy2) {

    float dx = x2 - x1;
    float dy = y2 - y1;

    float p[4] = { -dx, dx, -dy, dy };
    float q[4] = { x1 - xmin, xmax - x1, y1 - ymin, ymax - y1 };

    float u1 = 0.0, u2 = 1.0;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0)
                return false; // Line outside
        } else {
            float t = q[i] / p[i];
            if (p[i] < 0) {
                if (t > u1) u1 = t;
            } else {
                if (t < u2) u2 = t;
            }
        }
    }

    if (u1 > u2)
        return false;

    cx1 = x1 + u1 * dx;
    cy1 = y1 + u1 * dy;
    cx2 = x1 + u2 * dx;
    cy2 = y1 + u2 * dy;

    return true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

     glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    float x1 = 20, y1 = 200, x2 = 350, y2 = 200;

    if (!clipped) {
         glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    } else {
         float cx1, cy1, cx2, cy2;
        if (liangBarsky(x1, y1, x2, y2, cx1, cy1, cx2, cy2)) {
            glColor3f(1, 0, 0);
            glBegin(GL_LINES);
            glVertex2f(cx1, cy1);
            glVertex2f(cx2, cy2);
            glEnd();
        }
    }

    glFlush();
}

void timer(int) {
    clipped = true;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Liang-Barsky Line Clipping");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutTimerFunc(2000, timer, 0);  

    glutMainLoop();
    return 0;
}
