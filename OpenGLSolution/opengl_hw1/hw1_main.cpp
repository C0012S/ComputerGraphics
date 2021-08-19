#include <GL\glut.h>

// 전역 변수 선언
GLfloat tXr = 0.0, tYr = 0.0;
GLfloat tXt = 0.0, tYt = 0.0; //겹치면 안 되기 때문에 분리해 줘야 한다 //메뉴를 선택해야 이동이 된다
GLboolean isRec=true, isTri=false; //사각형을 default로 해 둔다
GLfloat Delta = 0.0;    // Timer

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(-1.5+tXr, 0.5+tYr, 0.0);
    glVertex3f(-0.3 + tXr, 0.5 + tYr, 0.0);
    glColor3f(0.0, 0.0, 1.0);   // Blue
    glVertex3f(-0.3 + tXr, 1.3 + tYr, 0.0);
    glVertex3f(-1.5 + tXr, 1.3 + tYr, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //옮기고 싶지 않으면 tX, tY 안 넣어 주면 된다
    glVertex3f(0.5 + tXt, -0.5 + tYt, 0.0); //변화된 값을 찍으므로 움직이는 것처럼 보인다
    glVertex3f(1.5 + tXt, -0.5 + tYt, 0.0);
    glVertex3f(1.0 + tXt, 0.5 + tYt, 0.0);
    glEnd();

    glColor3f(0.8, 0.0+Delta, 0.7); //원래는 핑크 //Timer의 값에 의해서 색이 바뀐다
    glutSolidTeapot(0.5+Delta); //Timer에 의해서 Teapot의 크기도 변한다

    //glFlush();
    glutSwapBuffers(); //더블 버퍼를 쓰기 때문에 glFlush(); 대신 쓴다
}

void MyReshape(int w, int h) {
        // => 창의 크기에 비례해서 창 안의 내용이 모델링
        // 창의 크기에 관계없이 창 안의 내용은 그대로 유지
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -2.5, 2.5);

//    gluPerspective(60.0f, 1, 0, 20); // 카메라의 시야각
//    gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0); // 카메라의 위치 gluLookAt(x, y, z, ...) //x, y, z만 기억하면 된다
//    gluLookAt(0, -1, 4, 0, 0, 0, 0, 1, 0); // 카메라의 위치 gluLookAt(x, y, z, ...) //카메라 아래쪽으로 보는 효과를 주고 싶다면 //아래에서 위로 보는 듯한 느낌

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'Q' : 
    case 'q' :
    case 27 : // ESC
        exit(0); break;     // window 종료
    }
    glutPostRedisplay();    // MyDisplay(); 호출 //그림 다시 그리고 싶을 때 호출
}

void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN: // 아래방향 화살표
        if (isRec)        tYr -= 0.1;
        else if (isTri)  tYt -= 0.1;
        break;
    case GLUT_KEY_UP:   // 위방향 화살표
        if (isRec)        tYr += 0.1;
        else if (isTri)  tYt += 0.1;
        break;
    case GLUT_KEY_LEFT: // 왼쪽방향 화살표
        if (isRec)        tXr -= 0.1;
        else if (isTri)  tXt -= 0.1;
        break;
    case GLUT_KEY_RIGHT:    // 오른쪽 방향 화살표
        if (isRec)      tXr += 0.1;
        else if (isTri)  tXt += 0.1;
        break;
    }
    glutPostRedisplay();    // MyDisplay(); 호출
}

void MyModelMenu(int entryID) {
    if (entryID == 1) { // 사각형 선택
        isRec = true;
        isTri = false;
    }
    else if (entryID == 2) { // 삼각형 선택
        isTri = true;
        isRec = false;
    }
    glutPostRedisplay(); 
}

void MyMainMenu(int entryID) {
    if (entryID == 9) exit(0);
}

void MyTimer(int Value) {
    Delta += 0.01;
    if (Delta > 1.0) Delta = 0.0;
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("My First Creative Graphics - OpenGL HW1");
    glClearColor(0.9, 1.0, 0.8, 1.0); // 창의 배경색

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecial);
    GLint MyModelID = glutCreateMenu(MyModelMenu);
    glutAddMenuEntry("사각형", 1); // 1 또는 2, ID, 중복되지 않게 선언 //1 말고 다른 값 써도 된다 //중복만 안 되면 된다
    glutAddMenuEntry("삼각형", 2);

    glutCreateMenu(MyMainMenu);
    glutAddSubMenu("모델", MyModelID); //서브 메뉴로 들어간다 //모델에 사각형, 삼각형이 서브 메뉴로 들어간다
    glutAddMenuEntry("Exit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutTimerFunc(40, MyTimer, 1); // 40msec //mesc = 1/1000 sec
    glutMainLoop();
    return 0;
}