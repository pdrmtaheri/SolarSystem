#include <GL/freeglut.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <math.h>

void display();

void reshape(int x, int y);

void keypress(unsigned char key, int x, int y);

void specialKeypress(int key, int x, int y);

//GLuint LoadTexture(const char *filename) {
//
//    GLuint texture;
//
//    int width, height;
//
//    unsigned char *data;
//
//    FILE *file;
//
//    file = fopen(filename, "rb");
//
//    if (file == NULL) return 0;
//    width = 1024;
//    height = 512;
//    data = (unsigned char *) malloc(width * height * 3);
//    //int size = fseek(file,);
//    fread(data, width * height * 3, 1, file);
//    fclose(file);
//
//    for (int i = 0; i < width * height; ++i) {
//        int index = i * 3;
//        unsigned char B, R;
//        B = data[index];
//        R = data[index + 2];
//
//        data[index] = R;
//        data[index + 2] = B;
//
//    }
//
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
//    free(data);
//
//    return texture;
//}

//GLuint earthTexture;
//GLuint sunTexture;
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(350, 350);
    glutCreateWindow("Solar System");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glEnable(GL_TEXTURE_2D);
    glCullFace(GL_BACK);

//    earthTexture = LoadTexture("/home/pedram/CLionProjects/SolarSystem/earth.bmpp");
//    sunTexture = LoadTexture("/home/pedram/CLionProjects/SolarSystem/sun.bmp");
//
//    std::cout << earthTexture << " " << sunTexture << std::endl;
//    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

    gluLookAt(0, 0, -5, 0, 0, 0, 0, 1, 0);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keypress);
    glutSpecialFunc(specialKeypress);

    glutMainLoop();

    return EXIT_SUCCESS;
}

unsigned int day = 0;

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex3f(x + cx, 0, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.9, 0.9, 0.1);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, sunTexture);
    glutSolidSphere(1.5, 20, 20);

    day += 1;
    if (day > std::numeric_limits<unsigned int>::max()) {
        day = 0;
    }
    glPushMatrix();
    glColor3f(0.6, 0.2, 0.2);
    DrawCircle(0, 0, 3, 25);
    glRotatef(day, 0, 1.0, 0);
    glTranslatef(0, 0, 3);
    glRotatef(day * 24, 0, 1, 0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, earthTexture);
    glutWireSphere(0.5, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.6, 0.2);
    DrawCircle(0, 0, 4, 35);
    glRotatef(day * 1.5, 0, 1.0, 0);
    glTranslatef(0, 0, 4);
    glRotatef(day * 5, 0, 1, 0);
    glutWireSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.2, 0.6);
    DrawCircle(0, 0, 5, 50);
    glRotatef(day * 1.2, 0, 1.0, 0);
    glTranslatef(0, 0, 5);
    glRotatef(day * 10, 0, 1, 0);
    glutWireSphere(0.2, 20, 20);
    glPopMatrix();

    std::this_thread::sleep_for(std::chrono::milliseconds(40));
    glFlush();
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLdouble) x / (GLdouble) y, 0.6, 30);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

void keypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(1, 0, 1, 0);
            glutPostRedisplay();
            break;
        case 'd':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(1, 0, -1, 0);
            glutPostRedisplay();
            break;
        case 'w':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(1, -1, 0, 0);
            glutPostRedisplay();
            break;
        case 's':
            glMatrixMode(GL_MODELVIEW);
            glRotatef(1, 1, 0, 0);
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

void specialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            glMatrixMode(GL_PROJECTION);
            glTranslatef(0, 0, 0.4);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            glMatrixMode(GL_PROJECTION);
            glTranslatef(0, 0, -0.4);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            glMatrixMode(GL_PROJECTION);
            glTranslatef(0.4, 0, 0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            glMatrixMode(GL_PROJECTION);
            glTranslatef(-0.4, 0, -0);
            glutPostRedisplay();
            break;
        default:
            break;
    }
}