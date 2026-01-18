#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

// ---------------------- Shader source ----------------------
const char* vertCode = R"(
#version 120
attribute vec2 coordinates;
uniform float scale;
void main() {
    gl_Position = vec4(coordinates * scale, 0.0, 1.0);
}
)";

const char* fragCode = R"(
#version 120
uniform vec3 color;
void main() {
    gl_FragColor = vec4(color, 1.0);
}
)";

GLuint program;
GLint coordLoc, colorLoc, scaleLoc;

// ---------------------- Parameters ----------------------
float gap = 0.05f;
float step = 0.3f;
float thick = 0.05f;
float height = 0.5f;
float halfStep = step / 2.0f;
float halfThick = thick / 2.0f;

// ---------------------- Utility ----------------------
GLuint compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);

    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, 512, nullptr, log);
        std::cerr << "Shader error:\n" << log << std::endl;
    }
    return s;
}

void drawPolygon(const std::vector<float>& v) {
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(coordLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(coordLoc);

    glDrawArrays(GL_TRIANGLE_FAN, 0, v.size() / 2);
    glDeleteBuffers(1, &VBO);
}

// ---------------------- Letters ----------------------
void drawLetterN(float x) {
    drawPolygon({x,-height, x,height, x+thick,height, x+thick,-height});
    drawPolygon({x+thick,height-4*thick, x+thick,height,
                 x+step-thick,-(height-4*thick), x+step-thick,-height});
    drawPolygon({x+step-thick,-height, x+step-thick,height,
                 x+step,height, x+step,-height});
}

void drawLetterI(float x) {
    drawPolygon({x,height-2*thick, x,height, x+step,height, x+step,height-2*thick});
    drawPolygon({x+halfStep-halfThick,-height, x+halfStep-halfThick,height,
                 x+halfStep+halfThick,height, x+halfStep+halfThick,-height});
    drawPolygon({x,-(height-2*thick), x,-height, x+step,-height, x+step,-(height-2*thick)});
}

void drawLetterR(float x) {
    drawPolygon({x,-height, x,height, x+thick,height, x+thick,-height});
    drawPolygon({x,height-2*thick, x,height, x+step,height, x+step,height-2*thick});
    drawPolygon({x+step-thick,0, x+step-thick,height, x+step,height, x+step,0});
    drawPolygon({x,2*thick, x,0, x+step,0, x+step,2*thick});
    drawPolygon({x,0, x,3*thick, x+step,-height, x+step-1.5f*thick,-height});
}

void drawLetterJ(float x) {
    drawPolygon({x,height-2*thick, x,height, x+step,height, x+step,height-2*thick});
    drawPolygon({x+thick+halfStep-halfThick,-height, x+thick+halfStep-halfThick,height,
                 x+thick+halfStep+halfThick,height, x+thick+halfStep+halfThick,-height});
    drawPolygon({x,-(height-2*thick), x,-height,
                 x+halfStep+halfThick,-height, x+halfStep+halfThick,-height+2*thick});
    drawPolygon({x,-height, x,-2*thick, x+thick,-2*thick, x+thick,-height});
}

void drawLetterA(float x) {
    drawPolygon({x,-height, x+halfStep-halfThick,height,
                 x+halfStep+halfThick,height, x+thick,-height});
    drawPolygon({x+step-thick,-height, x+halfStep-halfThick,height,
                 x+halfStep+halfThick,height, x+step,-height});
    drawPolygon({x+2*thick,-2*thick, x+2*thick,0,
                 x+step-2*thick,0, x+step-2*thick,-2*thick});
}

// ---------------------- Display ----------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float numLetters = 7;
    float totalWidth = (step + gap) * numLetters - gap;
    float scale = (2.0f / totalWidth) * 0.92f;
    glUniform1f(scaleLoc, scale);
    glUniform3f(colorLoc, 0.8f, 0.2f, 1.0f);

    float x = -totalWidth / 2.0f;

    drawLetterN(x); x += step + gap;
    drawLetterI(x); x += step + gap;
    drawLetterR(x); x += step + gap;
    drawLetterJ(x); x += step + gap;
    drawLetterA(x); x += step + gap;
    drawLetterR(x); x += step + gap;
    drawLetterA(x);

    glutSwapBuffers();
}

// ---------------------- Init ----------------------
void init() {
    glewInit();

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertCode);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragCode);

    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    coordLoc = glGetAttribLocation(program, "coordinates");
    colorLoc = glGetUniformLocation(program, "color");
    scaleLoc = glGetUniformLocation(program, "scale");

    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
}

// ---------------------- Main ----------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("NIRJARA - OpenGL");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
