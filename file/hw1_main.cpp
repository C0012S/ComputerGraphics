#include <GL\glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-1.5, 0.5, 0.0);
    glVertex3f(-0.3, 0.5, 0.0);
    glColor3f(0.0, 0.0, 1.0);   // Blue
    glVertex3f(-0.3, 1.3, 0.0);
    glVertex3f(-1.5, 1.3, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(1.5, -0.5, 0.0);
    glVertex3f(1.0, 0.5, 0.0);
    glEnd();

    glColor3f(0.8, 0.0, 0.7);
    glutSolidTeapot(0.5);

    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -2.5, 2.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("My First Creative Graphics - OpenGL HW1");
    glClearColor(0.9, 1.0, 0.8, 1.0); // 창의 배경색

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutMainLoop();
    return 0;
}
