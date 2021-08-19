#include <GL\glut.h>

// ���� ���� ����
GLfloat tXr = 0.0, tYr = 0.0;
GLfloat tXt = 0.0, tYt = 0.0; //��ġ�� �� �Ǳ� ������ �и��� ��� �Ѵ� //�޴��� �����ؾ� �̵��� �ȴ�
GLboolean isRec=true, isTri=false; //�簢���� default�� �� �д�
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

    glBegin(GL_TRIANGLES); //�ű�� ���� ������ tX, tY �� �־� �ָ� �ȴ�
    glVertex3f(0.5 + tXt, -0.5 + tYt, 0.0); //��ȭ�� ���� �����Ƿ� �����̴� ��ó�� ���δ�
    glVertex3f(1.5 + tXt, -0.5 + tYt, 0.0);
    glVertex3f(1.0 + tXt, 0.5 + tYt, 0.0);
    glEnd();

    glColor3f(0.8, 0.0+Delta, 0.7); //������ ��ũ //Timer�� ���� ���ؼ� ���� �ٲ��
    glutSolidTeapot(0.5+Delta); //Timer�� ���ؼ� Teapot�� ũ�⵵ ���Ѵ�

    //glFlush();
    glutSwapBuffers(); //���� ���۸� ���� ������ glFlush(); ��� ����
}

void MyReshape(int w, int h) {
        // => â�� ũ�⿡ ����ؼ� â ���� ������ �𵨸�
        // â�� ũ�⿡ ������� â ���� ������ �״�� ����
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -2.5, 2.5);

//    gluPerspective(60.0f, 1, 0, 20); // ī�޶��� �þ߰�
//    gluLookAt(0, 1, 4, 0, 0, 0, 0, 1, 0); // ī�޶��� ��ġ gluLookAt(x, y, z, ...) //x, y, z�� ����ϸ� �ȴ�
//    gluLookAt(0, -1, 4, 0, 0, 0, 0, 1, 0); // ī�޶��� ��ġ gluLookAt(x, y, z, ...) //ī�޶� �Ʒ������� ���� ȿ���� �ְ� �ʹٸ� //�Ʒ����� ���� ���� ���� ����

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'Q' : 
    case 'q' :
    case 27 : // ESC
        exit(0); break;     // window ����
    }
    glutPostRedisplay();    // MyDisplay(); ȣ�� //�׸� �ٽ� �׸��� ���� �� ȣ��
}

void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN: // �Ʒ����� ȭ��ǥ
        if (isRec)        tYr -= 0.1;
        else if (isTri)  tYt -= 0.1;
        break;
    case GLUT_KEY_UP:   // ������ ȭ��ǥ
        if (isRec)        tYr += 0.1;
        else if (isTri)  tYt += 0.1;
        break;
    case GLUT_KEY_LEFT: // ���ʹ��� ȭ��ǥ
        if (isRec)        tXr -= 0.1;
        else if (isTri)  tXt -= 0.1;
        break;
    case GLUT_KEY_RIGHT:    // ������ ���� ȭ��ǥ
        if (isRec)      tXr += 0.1;
        else if (isTri)  tXt += 0.1;
        break;
    }
    glutPostRedisplay();    // MyDisplay(); ȣ��
}

void MyModelMenu(int entryID) {
    if (entryID == 1) { // �簢�� ����
        isRec = true;
        isTri = false;
    }
    else if (entryID == 2) { // �ﰢ�� ����
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
    glClearColor(0.9, 1.0, 0.8, 1.0); // â�� ����

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutKeyboardFunc(MyKeyboard);
    glutSpecialFunc(MySpecial);
    GLint MyModelID = glutCreateMenu(MyModelMenu);
    glutAddMenuEntry("�簢��", 1); // 1 �Ǵ� 2, ID, �ߺ����� �ʰ� ���� //1 ���� �ٸ� �� �ᵵ �ȴ� //�ߺ��� �� �Ǹ� �ȴ�
    glutAddMenuEntry("�ﰢ��", 2);

    glutCreateMenu(MyMainMenu);
    glutAddSubMenu("��", MyModelID); //���� �޴��� ���� //�𵨿� �簢��, �ﰢ���� ���� �޴��� ����
    glutAddMenuEntry("Exit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutTimerFunc(40, MyTimer, 1); // 40msec //mesc = 1/1000 sec
    glutMainLoop();
    return 0;
}