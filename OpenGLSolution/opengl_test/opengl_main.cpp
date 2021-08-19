#include <GL\glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

//    glColor3f(0.5, 0.4, 0.3);
    glColor3f(1.0, 0.0, 0.0); // Red
    glPointSize(10.0);
    glLineWidth(5.0); //�� �β� 5.0���� ����

//    glBegin(GL_POINTS); //�ݵ�� glEnd�� �־�� �� //POLYGON ���·� ǥ��
    glBegin(GL_LINES);
        glVertex3f(0.0, 1.0, 0.0); //���� ���� ������ �ſ� �߿�
        glVertex3f(-1.0, 0.5, 0.0);
        glVertex3f(-1.0, -0.5, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(1.0, -0.5, 0.0);
        glVertex3f(1.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //4 ���� ���� �����ϰ� ���� ��ĥ�Ѵ�
        glColor3f(0.0, 1.0, 0.0); // Green //glBegin �ȿ��� ���� �ٲ� �� �� �ִ�
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.6, 0.0, 0.0);
        glColor3f(0.0, 0.0, 1.0); // Blue
        glVertex3f(0.6, 0.3, 0.0);
        glVertex3f(0.0, 0.3, 0.0);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("My First OpenGL");
    glClearColor(1.0, 1.0, 1.0, 1.0); // ����
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // â�� ��ǥ�� ����

    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    return 0;
}