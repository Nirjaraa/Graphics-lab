#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <cstdlib>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600


std::vector<float> data_values = {30, 20, 25, 25};
float colors[][3] = {
    {1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f}
};

int center_x = 400;
int center_y = 300;
int radius   = 200;


void draw_circle_points(int xc, int yc, int x, int y)
{
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}


void draw_circle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int p = 1 - r;

    glBegin(GL_POINTS);
    draw_circle_points(xc, yc, x, y);

    while (x < y)
    {
        x++;
        if (p < 0)
            p += 2 * x + 1;
        else
        {
            y--;
            p += 2 * (x - y) + 1;
        }
        draw_circle_points(xc, yc, x, y);
    }
    glEnd();
}


void fill_slice(int xc, int yc,
                int x_edge, int y_edge,
                int prev_x, int prev_y,
                float color[3])
{
    glColor3fv(color);
    glBegin(GL_TRIANGLES);
    glVertex2i(xc, yc);
    glVertex2i(prev_x, prev_y);
    glVertex2i(x_edge, y_edge);
    glEnd();
}

void draw_pie_chart(int xc, int yc, int r)
{
    float total = 0.0f;
    for (float v : data_values) total += v;

    float start_angle = 0.0f;

    for (int i = 0; i < data_values.size(); i++)
    {
        float slice_angle = (data_values[i] / total) * 360.0f;

        int prev_x = xc + r * cos(start_angle * M_PI / 180.0);
        int prev_y = yc + r * sin(start_angle * M_PI / 180.0);

        for (int angle = (int)start_angle;
             angle <= (int)(start_angle + slice_angle);
             angle++)
        {
            float rad = angle * M_PI / 180.0f;
            int x_edge = xc + r * cos(rad);
            int y_edge = yc + r * sin(rad);

            fill_slice(xc, yc, x_edge, y_edge, prev_x, prev_y, colors[i]);

            prev_x = x_edge;
            prev_y = y_edge;
        }
        start_angle += slice_angle;
    }

    glColor3f(1, 1, 1);
    draw_circle(xc, yc, r);
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_pie_chart(center_x, center_y, radius);
    glFlush();
}


void keyboard(unsigned char key, int, int)
{
    if (key == 27) 
        exit(0);
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pie Chart");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}
