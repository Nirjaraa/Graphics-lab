#include <GL/glut.h>

int win_width = 800, win_height = 800;
float angle = 0.0f;

void drawCube(float size) {
    glutWireCube(size);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(10,10,15, 0,0,0, 0,1,0);

    glColor3f(0.0f, 0.0f, 1.0f);
    glPushMatrix();
        glTranslatef(4.0f, 0.0f, 0.0f);
        glRotatef(angle, 1.0f, 1.0f, 0.0f);
        drawCube(2.0f);
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angle += 0.5f;
    if(angle > 360) angle -= 360;
    glutPostRedisplay();
}

void reshape(int w, int h) {
    if(h == 0) h = 1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("Proper 3D Rotation");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0,1);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
