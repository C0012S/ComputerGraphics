#include <GL\glut.h>
//���콺 �̺�Ʈ�κ��� ������ 2 ���� �� //Ŭ������ �� ������ ����, ���콺�� ������ �� ������ �� //2 ���� ���� �̿��ؼ� �����簢���� �׸��� �κ��� �ۼ� //�׸��� �׸��� �κ��̱� ������ MyDiplay �Լ��� ����
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    //�� ������ x, y ��ǥ�� �״�� ������ �ȴ� //�ٸ� ���̰� �ִ� ����, �츮 �� ���� ����
    // width = 500, height = 500 //�� �Ǵ� �׷� â�� ������� �׷��� �׷� â�� �̿��� �ָ� �Ǳ� ������ �Ʒ� ���� �״�� ������ �ȴ� //�״�� ������ �ͼ� x, y ��ǥ�� �ֵ� width�� 500.0, height�� 500.0���� �Ѵ�
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); // Green

    //MyDisplay�� �տ��� ����� 4 ���� ���� ��ǥ�� ����� ��� �Ѵ� //���ʴ�� ������
//    glVertex3f(-1.5, 0.5, 0.0); // (TopLeftX/width, (height-TopLeftY)/height)
    glVertex3f(TopLeftX / 500.0, (500 - TopLeftY) / 500.0, 0.0); //�и� �ش�Ǵ� �κ��� �Ҽ������� ǥ���� �ִ� ������ ��ü���� ����� �Ǽ� ������ ������ ���ֱ� ���ؼ� �� �κи� Ư���� 500�̶� ���� �ʰ� 500.0���� �� �Ŵ�
//    glVertex3f(-0.3, 0.5, 0.0); // (TopLeftX/width, (height-BottomRightY)/height)
    glVertex3f(TopLeftX / 500.0, (500 - BottomRightY) / 500.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);   // Blue
//    glVertex3f(-0.3, 1.3, 0.0); // (BottomRightX/width, (height-BottomRightY)/height)
    glVertex3f(BottomRightX / 500.0, (500 - BottomRightY) / 500.0, 0.0);

//    glVertex3f(-1.5, 1.3, 0.0); // (BottomRightX/width, (height-TopLeftY)/height)
    glVertex3f(BottomRightX / 500.0, (500 - TopLeftY) / 500.0, 0.0);
    glEnd();

/*    glBegin(GL_TRIANGLES);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(1.5, -0.5, 0.0);
    glVertex3f(1.0, 0.5, 0.0);
    glEnd();

    glColor3f(0.8, 0.0, 0.7);
    glutSolidTeapot(0.5);
*/

    glFlush();
}
//�׷��� ���� ���콺�� ���ؼ�, ���콺�� Ŭ���ϰ� �ٿ����� �� ���� 2 ���� ���� ��ǥ�� �̿��ؼ�, glutPostRedisplay();�� ���ؼ� ���콺�� ������ ������ MyDisplay()��� �Լ��� �Ҹ�������
//�� MyDisplay�� TopLeftX, TopLeftY, BottomLeftX, BottomLeftY�� �̿��ؼ� ���� �־��� ������ ũ��, �׸��� ���� ������ glOrtho�� �´� ��ǥ ���� ����ؼ�
//glVertex�� �̿��ؼ� �簢���� �׸��� �ȴ�
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -2.5, 2.5); //������ ��ǥ��� ���콺�� ��ġ�� ��ġ�ϱ� ���ؼ� x, y ��ǥ ��� ����� �ش�Ǵ� ������ �Ѵ� //�ش��ϴ� ��ǥ�� ���� �پ��ϰ� ���� �� ������, ���� �⺻�� �Ǵ� 1.0�� �ش�Ǵ� ��ǥ�� ������ �غ��� //��, x ��ǥ�� ���� ���� �� 0.0�������� 1.0, y ��ǥ�� ��������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y) { //MyMouseFunc�� ���ؼ� ��ϵ� �Լ��̹Ƿ� �Ű� ������ � ��ư�� ���ȴ���, �Ǵ� ���� ��ư�� ���´� ���(down���� up����), ���콺�� ��ġ //�� �ȿ� ���콺�� Ŭ���Ǿ��� �� �ش��ϴ� ��ɾ� ����
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        TopLeftX = x;
        TopLeftY = y;
    }
} //���콺�� Ŭ������ ���� ���� �ϳ�

void MyMouseMove(GLint x, GLint y) { //��ư�� ���� ���¿��� �����δٰ� �ϱ� ������ button�̳� state�� ���� ���� ���� ������ ��ġ ���� �Ű� ������ ���� //�� �ȿ� ���콺�� ������ ���� �ش�Ǵ� ��ɾ� ����
    BottomRightX = x;
    BottomRightY = y;
    glutPostRedisplay(); //2 ���� ���� ������ �簢���� �׸� �� �ִ� �簢���� �׸��� ���ؼ� MyDisplay�� ȣ���ؾ� �Ѵ� //���� ȣ���ϴ� �� �� �Լ��� ���ؼ� ���������� ȣ���� �� �ִ�
} //���콺�� ������ ������ �� �ٸ� ���� ���ܼ� 2 ���� ���� �����

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(900, 900); //���� �츮�� (900, 900)�� �ش�Ǵ� ũ���� �������� ����� ���� �ִ�
    glutInitWindowSize(500, 500); //�ٸ� ���ڷ� �ٲ㵵 �ȴ� //�� ���� �������� ũ�Ⱑ �̰ű���, ��� �˸� �ȴ�
    glutInitWindowPosition(200, 100);

    glutCreateWindow("My First Creative Graphics - OpenGL HW1");
    glClearColor(0.9, 1.0, 0.8, 1.0); // â�� ����

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick); //�ݹ� �Լ� ���
    glutMotionFunc(MyMouseMove); //���콺�� �巡�׵Ǵ� �̺�Ʈ�� ó���� �ֱ� ���ؼ� glutMotionFunc //�ݹ� �Լ� ���

    glutMainLoop();
    return 0;
}