#include <GL\glut.h>

//���� ���� ����
GLfloat Delta = 0.0;    // Timer - �ð����� ���ϴ� �� �����ϴ� ����
GLboolean isBoat = true, isGreenFish = false, isYellowFish = false, isRedFish = false; //���õ� ��ü�� true ���� �����ϴ� ����
GLfloat tXb = 0.0, tYb = 0.0; //��Ʈ�� ������ �� �����ϴ� ����
GLfloat tXfg = 0.0, tYfg = 0.0; //�ʷϻ� ����Ⱑ ������ �� �����ϴ� ����
GLfloat tXfy = 0.0, tYfy = 0.0; //����� ����Ⱑ ������ �� �����ϴ� ����
GLfloat tXfr = 0.0, tYfr = 0.0; //������ ����Ⱑ ������ �� �����ϴ� ����

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); //�� ����� �׸���
    glColor3f(1.0, 1.0, 0.0); // �����
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

    glBegin(GL_POLYGON); //�ٴٸ� �׸���
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex3f(-3.0, -1.0, 0.0);
    glVertex3f(-3.0, -3.0, 0.0);
    glVertex3f(3.0, -3.0, 0.0);
    glVertex3f(3.0, -1.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //�踦 �׸��� (�ٴ� �κ�)
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(-0.6 + tXb, -1.0 + tYb, 0.0);
    glVertex3f(0.6 + tXb, -1.0 + tYb, 0.0);
    glVertex3f(1.0 + tXb, -0.5 + tYb, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //�� ��븦 �׸���
    glColor3f(1.0, 1.0, 1.0); // White
    glVertex3f(-0.05 + tXb, 0.5 + tYb, 0.0);
    glVertex3f(-0.05 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(0.05 + tXb, -0.5 + tYb, 0.0);
    glVertex3f(0.05 + tXb, 0.5 + tYb, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //�� ����� �׸���
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(0.05 + tXb, 0.5 + tYb, 0.0);
    glVertex3f(0.5 + tXb, 0.25 + tYb, 0.0);
    glVertex3f(0.05 + tXb, 0.0 + tYb, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //�ʷϻ� ����� �Ӹ��� ������ �׸���
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(1.1 + tXfg, -2.0 + tYfg, 0.0);
    glVertex3f(1.0 + tXfg, -1.9 + tYfg, 0.0);
    glVertex3f(1.1 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -2.0 + tYfg, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //�ʷϻ� ����� ������ �׸���
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex3f(1.4 + tXfg, -1.8 + tYfg, 0.0);
    glVertex3f(1.3 + tXfg, -1.9 + tYfg, 0.0);
    glVertex3f(1.4 + tXfg, -2.0 + tYfg, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //����� ����� �Ӹ��� ������ �׸���
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(0.1 + tXfy, -2.4 + tYfy, 0.0);
    glVertex3f(0.0 + tXfy, -2.3 + tYfy, 0.0);
    glVertex3f(0.1 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.4 + tYfy, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //����� ����� ������ �׸���
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex3f(0.4 + tXfy, -2.2 + tYfy, 0.0);
    glVertex3f(0.3 + tXfy, -2.3 + tYfy, 0.0);
    glVertex3f(0.4 + tXfy, -2.4 + tYfy, 0.0);
    glEnd();

    glBegin(GL_POLYGON); //������ ����� �Ӹ��� ������ �׸���
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-1.1 + tXfr, -1.5 + tYfr, 0.0);
    glVertex3f(-1.2 + tXfr, -1.4 + tYfr, 0.0);
    glVertex3f(-1.1 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.5 + tYfr, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES); //������ ����� ������ �׸���
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex3f(-0.8 + tXfr, -1.3 + tYfr, 0.0);
    glVertex3f(-0.9 + tXfr, -1.4 + tYfr, 0.0);
    glVertex3f(-0.8 + tXfr, -1.5 + tYfr, 0.0);
    glEnd();

    glFlush();
}

void MyReshape(int w, int h) {
    // => â�� ũ�⿡ ����ؼ� â ���� ������ �𵨸� 
    // â�� ũ�⿡ ������� â���� ������ �״�� ����
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -2.5, 2.5);

//    gluPerspective(60.0f, 1, 0, 20);    // ī�޶��� �þ߰�
//    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0); // ī�޶��� ��ġ gluLookAt(x,y,z, ...)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void MyTimer(int Value) { //�� ����� �׸� ��ǥ�� ���� ���� ���� Ŀ�� �� �ֵ��� 40msec���� �����ϴ� ���� Delta�� �����Ѵ�.
    Delta += 0.005;
    if (Delta > 0.2) Delta = 0.0; //Delta�� 0.2 �̻��̸� 0.0���� �ʱ�ȭ�Ѵ�.
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}


void MyMainMenu(int entryID) {
    if (entryID == 1) { //�� ����
        isBoat = true;
    }

    else if (entryID == 9) { //����
        exit(0);
    }

    glutPostRedisplay();
}

void MyFishMenu(int entryID) { 
    if (entryID == 1) { //�ʷϻ� ����� ����
        isGreenFish = true;
        isYellowFish = false;
        isRedFish = false;
        isBoat = false;
    }
    else if (entryID == 2) { //����� ����� ����
        isGreenFish = false;
        isYellowFish = true;
        isRedFish = false;
        isBoat = false;
    }
    else if (entryID == 3) { //������ ����� ����
        isGreenFish = false;
        isYellowFish = false;
        isRedFish = true;
        isBoat = false;
    }

    glutPostRedisplay();
}


void MySpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN: // �Ʒ����� ȭ��ǥ
        if (isBoat)        tYb -= 0.1;
        else if (isGreenFish)      tYfg -= 0.1;
        else if (isYellowFish)      tYfy -= 0.1;
        else if (isRedFish)      tYfr -= 0.1;
        break;

    case GLUT_KEY_UP:   // ������ ȭ��ǥ
        if (isBoat)        tYb += 0.1;
        else if (isGreenFish)      tYfg += 0.1;
        else if (isYellowFish)      tYfy += 0.1;
        else if (isRedFish)      tYfr += 0.1;
        break;

    case GLUT_KEY_LEFT: // ���ʹ��� ȭ��ǥ
        if (isBoat)      tXb -= 0.1;
        else if (isGreenFish) tXfg -= 0.1;
        else if (isYellowFish) tXfy -= 0.1;
        else if (isRedFish) tXfr -= 0.1;
        break;

    case GLUT_KEY_RIGHT:// �����ʹ��� ȭ��ǥ
        if (isBoat)        tXb += 0.1;
        else if (isGreenFish)    tXfg += 0.1;
        else if (isYellowFish)    tXfy += 0.1;
        else if (isRedFish)    tXfr += 0.1;
        break;
    }
    glutPostRedisplay(); // MyDisplay(); ȣ��
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200, 100);

    glutCreateWindow("1005 OpenGL HW1");
    glClearColor(0, 0, 0, 0); // â�� ���� - ������

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutTimerFunc(40, MyTimer, 1);  //40msec

    glutSpecialFunc(MySpecial);

    GLint MyFishID = glutCreateMenu(MyFishMenu); //����� �޴��� �� ���� �޴� ����
    glutAddMenuEntry("�ʷϻ�", 1);
    glutAddMenuEntry("�����", 2);
    glutAddMenuEntry("������", 3);

    GLint MyMainID = glutCreateMenu(MyMainMenu); //���� �޴� ����
    glutAddMenuEntry("��Ʈ", 1);  // ID �ߺ����� �ʰ� ����
    glutAddSubMenu("�����", MyFishID);
    glutAddMenuEntry("Exit", 9);
    glutAttachMenu(GLUT_RIGHT_BUTTON); //���콺�� ������ ��ư�� Ŭ���ϸ� �޴��� ��Ÿ���� �Ѵ�

    glutMainLoop();
    return 0;
}
