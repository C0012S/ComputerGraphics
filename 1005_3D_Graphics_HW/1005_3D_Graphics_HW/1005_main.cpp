#include <GL\glut.h>

//전역 변수 선언
GLfloat Delta = 0.0;    // Timer - 시간마다 변하는 값 저장하는 변수
GLboolean isBoat = true, isGreenFish = false, isYellowFish = false, isRedFish = false; //선택된 물체에 true 값을 저장하는 변수
GLfloat tXb = 0.0, tYb = 0.0; //보트가 움직일 값 저장하는 변수
GLfloat tXfg = 0.0, tYfg = 0.0; //초록색 물고기가 움직일 값 저장하는 변수
GLfloat tXfy = 0.0, tYfy = 0.0; //노란색 물고기가 움직일 값 저장하는 변수
GLfloat tXfr = 0.0, tYfr = 0.0; //빨간색 물고기가 움직일 값 저장하는 변수

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); //별 모양을 그린다
    glColor3f(1.0, 1.0, 0.0); // 노란색
    glVertex3f(1.8, 1 - Delta, 0.0);
    glVertex3f(2.3, 0.8 - Delta, 0.0);
    glVertex3f(2.1, 1.2, 0.0);
    glVertex3f(2.4, 1.6 + Delta, 0.0);
    glVertex3f(2.0, 1.6 + Delta, 0.0);
    glVertex3f(1.8, 2.0 + Delta, 0.0);
    glVertex3f(1.6, 1.6 + Delta, 0.0);
    glVertex3f(1.2, 1.6 + Delta, 0.0);
    glVertex3f(1.5, 1.2, 0.0);
    glVertex3f(1.3, 0.8 - Delta, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //바다를 그린다
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-3.0, -1.0, 0.0);
    glVertex3f(-3.0, -3.0, 0.0);
    glVertex3f(3.0, -3.0, 0.0);
    glVertex3f(3.0, -1.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //배를 그린다 (바닥 부분)
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(-0.6 + tXb, -1.0 + tYb, 0.0);
    glVertex3f(0.6 + tXb, -1.0 + tYb, 0.0);
    glVertex3f(1.0 + tXb, -0.5 + tYb, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //배 깃대를 그린다
    glColor3f(1.0, 1.0, 1.0); // White
    glVertex3f(-0.05 + tXb, 0.5 + tYb, 0.0);
    glVertex3f(-0.05 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(0.05 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(0.05 + tXb, 0.5 + tYb, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //배 깃발을 그린다
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(0.05 + tXb, 0.5 + tYb, 0.0);
    glVertex3f(0.5 + tXb, 0.25 + tYb, 0.0);
    glVertex3f(0.05 + tXb, 0.0 + tYb, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //초록색 물고기 머리와 몸통을 그린다
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(1.1 + tXfg, -2.0 + tYfg, 0.0);
    glVertex3f(1.0 + tXfg, -1.9 + tYfg, 0.0);
    glVertex3f(1.1 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -2.0 + tYfg, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //초록색 물고기 꼬리를 그린다
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(1.4 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -1.9 + tYfg, 0.0);
    glVertex3f(1.4 + tXfg, -2.0 + tYfg, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //노란색 물고기 머리와 몸통을 그린다
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(0.1 + tXfy, -2.4 + tYfy, 0.0);
    glVertex3f(0.0 + tXfy, -2.3 + tYfy, 0.0);
    glVertex3f(0.1 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.4 + tYfy, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //노란색 물고기 꼬리를 그린다
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(0.4 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.3 + tYfy, 0.0);
    glVertex3f(0.4 + tXfy, -2.4 + tYfy, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //빨간색 물고기 머리와 몸통을 그린다
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.1 + tXfr, -1.5 + tYfr, 0.0);
    glVertex3f(-1.2 + tXfr, -1.4 + tYfr, 0.0);
    glVertex3f(-1.1 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.5 + tYfr, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //빨간색 물고기 꼬리를 그린다
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-0.8 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.4 + tYfr, 0.0);
    glVertex3f(-0.8 + tXfr, -1.5 + tYfr, 0.0);
    glEnd();

    glFlush();
}

void MyReshape(int w, int h) {
    // => 창의 크기에 비례해서 창 안의 내용이 모델링 
    // 창의 크기에 관계없이 창안의 내용은 그대로 유지
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -2.5, 2.5);

//    gluPerspective(60.0f, 1, 0, 20);    // 카메라의 시야각
//    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0); // 카메라의 위치 gluLookAt(x,y,z, ...)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void MyTimer(int Value) { //별 모양을 그린 좌표에 값을 더해 별이 커질 수 있도록 40msec마다 증가하는 값을 Delta에 저장한다.
    Delta += 0.005;
    if (Delta > 0.2) Delta = 0.0; //Delta가 0.2 이상이면 0.0으로 초기화한다.
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}


void MyMainMenu(int entryID) {
    if (entryID == 1) { //배 선택
        isBoat = true;
    }

    else if (entryID == 9) { //종료
        exit(0);
    }

    glutPostRedisplay();
}

void MyFishMenu(int entryID) { 
    if (entryID == 1) { //초록색 물고기 선택
        isGreenFish = true;
        isYellowFish = false;
        isRedFish = false;
        isBoat = false;
    }
    else if (entryID == 2) { //노란색 물고기 선택
        isGreenFish = false;
        isYellowFish = true;
        isRedFish = false;
        isBoat = false;
    }
    else if (entryID == 3) { //빨간색 물고기 선택
        isGreenFish = false;
        isYellowFish = false;
        isRedFish = true;
        isBoat = false;
    }

    glutPostRedisplay();
}


void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN: // 아래방향 화살표
        if (isBoat)        tYb -= 0.1;
        else if (isGreenFish)      tYfg -= 0.1;
        else if (isYellowFish)      tYfy -= 0.1;
        else if (isRedFish)      tYfr -= 0.1;
        break;

    case GLUT_KEY_UP:   // 위방향 화살표
        if (isBoat)        tYb += 0.1;
        else if (isGreenFish)      tYfg += 0.1;
        else if (isYellowFish)      tYfy += 0.1;
        else if (isRedFish)      tYfr += 0.1;
        break;

    case GLUT_KEY_LEFT: // 왼쪽방향 화살표
        if (isBoat)      tXb -= 0.1;
        else if (isGreenFish) tXfg -= 0.1;
        else if (isYellowFish) tXfy -= 0.1;
        else if (isRedFish) tXfr -= 0.1;
        break;

    case GLUT_KEY_RIGHT:// 오른쪽방향 화살표
        if (isBoat)        tXb += 0.1;
        else if (isGreenFish)    tXfg += 0.1;
        else if (isYellowFish)    tXfy += 0.1;
        else if (isRedFish)    tXfr += 0.1;
        break;
    }
    glutPostRedisplay(); // MyDisplay(); 호출
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("1005 OpenGL HW1");
    glClearColor(0, 0, 0, 0); // 창의 배경색 - 검은색

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutTimerFunc(40, MyTimer, 1);  //40msec

    glutSpecialFunc(MySpecial);

    GLint MyFishID = glutCreateMenu(MyFishMenu); //물고기 메뉴에 들어갈 서브 메뉴 구성
    glutAddMenuEntry("초록색", 1);
    glutAddMenuEntry("노란색", 2);
    glutAddMenuEntry("빨간색", 3);

    GLint MyMainID = glutCreateMenu(MyMainMenu); //메인 메뉴 생성
    glutAddMenuEntry("보트", 1);  // ID 중복되지 않게 선언
    glutAddSubMenu("물고기", MyFishID);
    glutAddMenuEntry("Exit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //마우스의 오른쪽 버튼을 클릭하면 메뉴가 나타나게 한다

    glutMainLoop();
    return 0;
}
