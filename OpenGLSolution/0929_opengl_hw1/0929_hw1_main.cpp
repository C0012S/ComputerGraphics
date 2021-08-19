#include <GL\glut.h>
//마우스 이벤트로부터 들어오는 2 개의 점 //클릭했을 때 들어오는 점과, 마우스가 움직일 때 들어오는 점 //2 개의 점을 이용해서 직각사각형을 그리는 부분을 작성 //그림을 그리는 부분이기 때문에 MyDiplay 함수를 수정
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    //이 내용을 x, y 좌표에 그대로 넣으면 된다 //다만 차이가 있는 것은, 우리 예 같은 경우는
    // width = 500, height = 500 //이 되는 그런 창을 만들었다 그래서 그런 창을 이용해 주면 되기 때문에 아래 값을 그대로 넣으면 된다 //그대로 가지고 와서 x, y 좌표에 넣되 width는 500.0, height는 500.0으로 한다
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0); // Green

    //MyDisplay에 앞에서 계산한 4 개의 점의 좌표를 계산해 줘야 한다 //차례대로 넣으면
//    glVertex3f(-1.5, 0.5, 0.0); // (TopLeftX/width, (height-TopLeftY)/height)
    glVertex3f(TopLeftX / 500.0, (500 - TopLeftY) / 500.0, 0.0); //분모에 해당되는 부분을 소수점으로 표현해 주는 이유는 전체적인 계산이 실수 값으로 나오게 해주기 위해서 이 부분만 특별히 500이라 하지 않고 500.0으로 한 거다
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
//그래서 이제 마우스에 의해서, 마우스를 클릭하고 다운했을 때 들어온 2 개의 점의 좌표를 이용해서, glutPostRedisplay();에 의해서 마우스가 움직일 때마다 MyDisplay()라는 함수가 불리어지고
//이 MyDisplay는 TopLeftX, TopLeftY, BottomLeftX, BottomLeftY를 이용해서 현재 주어진 윈도우 크기, 그리고 현재 설정된 glOrtho에 맞는 좌표 값을 계산해서
//glVertex를 이용해서 사각형을 그리게 된다
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, 1.0, 0.0, 1.0, -2.5, 2.5); //가급적 좌표계와 마우스의 위치와 일치하기 위해서 x, y 좌표 모두 양수에 해당되는 값으로 한다 //해당하는 좌표의 값도 다양하게 넣을 수 있지만, 가장 기본이 되는 1.0에 해당되는 좌표로 설정을 해본다 //즉, x 좌표에 제일 작은 값 0.0에서부터 1.0, y 좌표도 마찬가지
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y) { //MyMouseFunc에 의해서 등록된 함수이므로 매개 변수가 어떤 버튼이 눌렸는지, 또는 지금 버튼의 상태는 어떤가(down인지 up인지), 마우스의 위치 //이 안에 마우스가 클릭되었을 때 해당하는 명령어 삽입
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        TopLeftX = x;
        TopLeftY = y;
    }
} //마우스가 클릭됐을 때는 점이 하나

void MyMouseMove(GLint x, GLint y) { //버튼이 눌린 상태에서 움직인다고 하기 때문에 button이나 state에 대한 정보 없이 현재의 위치 값만 매개 변수로 전달 //이 안에 마우스가 움직일 때에 해당되는 명령어 삽입
    BottomRightX = x;
    BottomRightY = y;
    glutPostRedisplay(); //2 개의 점을 가지고 사각형을 그릴 수 있다 사각형을 그리기 위해선 MyDisplay를 호출해야 한다 //직접 호출하는 게 이 함수를 통해서 간접적으로 호출할 수 있다
} //마우스가 움직일 때마다 또 다른 점이 생겨서 2 개의 점이 생긴다

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(900, 900); //현재 우리는 (900, 900)에 해당되는 크기의 윈도우즈 사이즈를 쓰고 있다
    glutInitWindowSize(500, 500); //다른 숫자로 바꿔도 된다 //아 지금 윈도우의 크기가 이거구나, 라고 알면 된다
    glutInitWindowPosition(200, 100);

    glutCreateWindow("My First Creative Graphics - OpenGL HW1");
    glClearColor(0.9, 1.0, 0.8, 1.0); // 창의 배경색

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutMouseFunc(MyMouseClick); //콜백 함수 등록
    glutMotionFunc(MyMouseMove); //마우스가 드래그되는 이벤트를 처리해 주기 위해서 glutMotionFunc //콜백 함수 등록

    glutMainLoop();
    return 0;
}