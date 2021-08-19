#include <GL\glut.h>

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

//    glColor3f(0.5, 0.4, 0.3);
    glColor3f(1.0, 0.0, 0.0); // Red
    glPointSize(10.0);
    glLineWidth(5.0); //선 두께 5.0으로 변경

//    glBegin(GL_POINTS); //반드시 glEnd가 있어야 함 //POLYGON 형태로 표현
    glBegin(GL_LINES);
        glVertex3f(0.0, 1.0, 0.0); //점이 들어가는 순서가 매우 중요
        glVertex3f(-1.0, 0.5, 0.0);
        glVertex3f(-1.0, -0.5, 0.0);
        glVertex3f(0.0, -1.0, 0.0);
        glVertex3f(1.0, -0.5, 0.0);
        glVertex3f(1.0, 0.5, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //4 개의 점을 연결하고 안을 색칠한다
        glColor3f(0.0, 1.0, 0.0); // Green //glBegin 안에서 색을 바꿔 줄 수 있다
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
    glClearColor(1.0, 1.0, 1.0, 1.0); // 배경색
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // 창의 좌표축 선언

    glutDisplayFunc(MyDisplay);

    glutMainLoop();
    return 0;
}