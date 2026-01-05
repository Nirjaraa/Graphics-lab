#include <GL/glut.h>
#include <vector>
using namespace std;

// Clipping window
float xmin = 50, ymin = 50, xmax = 300, ymax = 300;

// Animation flag
bool clipped = false;

// Check if point is inside edge
bool inside(float x, float y, int edge) {
    if (edge == 0) return x >= xmin; // Left
    if (edge == 1) return x <= xmax; // Right
    if (edge == 2) return y >= ymin; // Bottom
    return y <= ymax;                // Top
}

// Find intersection point
pair<float, float> intersect(pair<float, float> a,
                             pair<float, float> b, int edge) {
    float x, y;
    float dx = b.first - a.first;
    float dy = b.second - a.second;

    if (edge == 0) { // Left
        x = xmin;
        y = a.second + dy * (xmin - a.first) / dx;
    }
    if (edge == 1) { // Right
        x = xmax;
        y = a.second + dy * (xmax - a.first) / dx;
    }
    if (edge == 2) { // Bottom
        y = ymin;
        x = a.first + dx * (ymin - a.second) / dy;
    }
    if (edge == 3) { // Top
        y = ymax;
        x = a.first + dx * (ymax - a.second) / dy;
    }

    return {x, y};
}

// Sutherland–Hodgman Algorithm
vector<pair<float, float>> clipPolygon(vector<pair<float, float>> poly) {
    for (int edge = 0; edge < 4; edge++) {
        vector<pair<float, float>> output;

        for (int i = 0; i < poly.size(); i++) {
            auto curr = poly[i];
            auto prev = poly[(i + poly.size() - 1) % poly.size()];

            bool currIn = inside(curr.first, curr.second, edge);
            bool prevIn = inside(prev.first, prev.second, edge);

            if (currIn) {
                if (!prevIn)
                    output.push_back(intersect(prev, curr, edge));
                output.push_back(curr);
            }
            else if (prevIn) {
                output.push_back(intersect(prev, curr, edge));
            }
        }
        poly = output;
    }
    return poly;
}

// Draw polygon as LINE (no fill)
void drawPolygon(vector<pair<float, float>> poly) {
    glBegin(GL_LINE_LOOP);
    for (auto p : poly)
        glVertex2f(p.first, p.second);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Pentagon (5 vertices)
    vector<pair<float, float>> pentagon = {
        {30, 120},
        {120, 360},
        {320, 300},
        {360, 150},
        {180, 30}
    };

    if (!clipped) {
        // BEFORE CLIPPING
        glColor3f(0.6, 0.6, 0.6);
        drawPolygon(pentagon);
    } else {
        // AFTER CLIPPING
        glColor3f(1, 0, 0);
        drawPolygon(clipPolygon(pentagon));
    }

    glFlush();
}

// Timer for animation
void timer(int) {
    clipped = true;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutTimerFunc(2000, timer, 0); // 2-second delay

    glutMainLoop();
    return 0;
}
