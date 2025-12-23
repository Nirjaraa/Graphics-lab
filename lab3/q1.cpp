#include <GL/glut.h>
#include <cmath>

 void plotPoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
}

 void midpointEllipse(int xc, int yc, int rx, int ry) {
    int x = 0;
    int y = ry;

    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int dx = 2 * ry2 * x;
    int dy = 2 * rx2 * y;

    float d1 = ry2 - rx2 * ry + 0.25f * rx2;

    glBegin(GL_POINTS);

     while (dx < dy) {
        plotPoints(xc, yc, x, y);
        if (d1 < 0) {
            x++;
            dx += 2 * ry2;
            d1 += dx + ry2;
        } else {
            x++;
            y--;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d1 += dx - dy + ry2;
        }
    }

     float d2 = ry2 * (x + 0.5f) * (x + 0.5f) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    while (y >= 0) {
        plotPoints(xc, yc, x, y);
        if (d2 > 0) {
            y--;
            dy -= 2 * rx2;
            d2 += rx2 - dy;
        } else {
            y--;
            x++;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d2 += dx - dy + rx2;
        }
    }

    glEnd();
}

 void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);

    midpointEllipse(0, 0, 250, 100); 

    glFlush();
}

 int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse - C++ OpenGL");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
