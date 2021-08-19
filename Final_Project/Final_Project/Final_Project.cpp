#include <stdio.h>
#include <GL\glaux.h>
#include <GL\glut.h>
#include <GL\glu.h>
#include <math.h>
#include <GL\gl.h>
#include "tga.h"

#define TEXTURE_NUM 5
GLuint texture[TEXTURE_NUM];
char texture_name[TEXTURE_NUM][100] = { "Gray.bmp", "FloorAndWallTexture.bmp", "White.bmp", "Black.bmp", "Orange.bmp" };
GLUquadricObj* qobj;

//float g_fDistance = -4.5f;
//float g_fSpinX = 0.0f;
//float g_fSpinY = 0.0f;

float fraction = 0.1f;
static float angle = 0.0; // Y 축을 중심으로 회전할 때의 회전각 - 카메라 회전과 관련
static float x = 2.25f, y = -0.5f, z = 10.0f; // 카메라의 위치
static float lx = 0.0f, ly = 0.0f, lz = -1.0f; // 시선의 방향을 나타내는 벡터

GLboolean isTime = true;
GLfloat Delta = 0.0f;
GLfloat open = 0.0f;
GLfloat wait = 0.0f;

GLuint g_textureID = -1;
boolean g_bBlending = true;
boolean isLight = false;

GLuint     filter, envtexture[6];
GLUquadricObj* quadratic;
boolean isEnv = false;

GLuint p_textureID[4];
int winddir = 45;
GLfloat windspeed = 0.0005f;
boolean isSnow = false;

struct Vertex {
    float tu, tv;
    float x, y, z;
};

Vertex g_FrontVertices[] = {
    { 0.0f,0.0f, 1.3f, -1.7f, 1.7f },
    { 1.0f,0.0f, 3.4f, -1.7f, 1.7f },
    { 1.0f,1.0f, 3.4f, 0.4, 1.7f },
    { 0.0f,1.0f, 1.3f, 0.4, 1.7f },

    { 1.0f,0.0f, 1.3f, -1.7f, -0.4f },
    { 1.0f,1.0f, 1.3f, 0.4f, -0.4f },
    { 0.0f,1.0f, 3.4f, 0.4f, -0.4f },
    { 0.0f,0.0f, 3.4f, -1.7f, -0.4f },

    { 0.0f,1.0f, 1.3f, 0.4f, -0.4f },
    { 0.0f,0.0f, 1.3f, 0.4f, 1.7f },
    { 1.0f,0.0f, 3.4f, 0.4f, 1.7f },
    { 1.0f,1.0f, 3.4f, 0.4f, -0.4f },

    { 1.0f,1.0f, 1.3f, -1.7f, -0.4f },
    { 0.0f,1.0f, 3.4f, -1.7f, -0.4f },
    { 0.0f,0.0f, 3.4f, -1.7f, 1.7f },
    { 1.0f,0.0f, 1.3f, -1.7f, 1.7f },

    { 1.0f,0.0f, 3.4f, -1.7f, -0.4f },
    { 1.0f,1.0f, 3.4f, 0.4f, -0.4f },
    { 0.0f,1.0f, 3.4f, 0.4f, 1.7f },
    { 0.0f,0.0f, 3.4f, -1.7f, 1.7f },

    { 0.0f,0.0f, 1.3f, -1.7f, -0.4f },
    { 1.0f,0.0f, 1.3f, -1.7f, 1.7f },
    { 1.0f,1.0f, 1.3f, 0.4f, 1.7f },
    { 0.0f,1.0f, 1.3f, 0.4f, -0.4f }
};

void loadTexture(void)
{
    tgaImageFile tgaImage;
    tgaImage.load((char*)"radiation_box.tga"); // tga 파일 필요 // (char *)로 캐스트 

    glGenTextures(1, &g_textureID);

    glBindTexture(GL_TEXTURE_2D, g_textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, tgaImage.m_texFormat,
        tgaImage.m_nImageWidth, tgaImage.m_nImageHeight,
        0, tgaImage.m_texFormat, GL_UNSIGNED_BYTE,
        tgaImage.m_nImageData);
}

void MyLightInit() { // 스포트라이트
    GLfloat global_ambient[] = { 0.5, 0.5, 0.5, 1.0 }; // 전역 주변 반사

    GLfloat Light0_Ambient[] = { 1.0, 1.0, 1.0, 1.0 }; // 0 번 광원 특성
    GLfloat Light0_Diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat Light0_Specular[] = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat Light1_Ambient[] = { 0.5, 0.5, 0.5, 1.0 }; // 1 번 광원 특성
    GLfloat Light1_Diffuse[] = { 0.5, 0.5, 0.5, 0.5 };
    GLfloat Light1_Specular[] = { 0.0, 0.0, 0.0, 1.0 };

    GLfloat Light0_Position[] = { 0.0, 1.0, 1.0, 1.0 }; // 0 번 광원 위치
    GLfloat Light0_Direction[] = { 0.0, -1.0, 0.0 }; // 0 번 광원 방향
    GLfloat Light0_Cutoff[] = { 35.0 }; // 0 번 광원 각도

    GLfloat Light1_Position[] = { 0.0, 1.0, 1.0, 1.0 }; // 1 번 광원 위치

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient); // 0 번 광원 특성 할당
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light0_Specular);

    glLightfv(GL_LIGHT1, GL_AMBIENT, Light0_Ambient); // 1 번 광원 특성 할당
    glLightfv(GL_LIGHT1, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, Light0_Specular);

    glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position); // 스포트라이트
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Light0_Direction); // 방향
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, Light0_Cutoff); // 각도
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0); // 코사인 승수

    GLfloat material_ambient[] = { 0.0, 0.0, 0.0, 1.0 }; // 물체 특성
    GLfloat material_diffuse[] = { 1.0, 1.0, 0.3, 1.0 };
    GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat material_shininess[] = { 127.0 };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse); // 물체 특성 할당
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient); // 전역 주변 반사
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // 근접 시점

    glShadeModel(GL_SMOOTH); // Gouraud Shading
    glEnable(GL_DEPTH_TEST); // 깊이 버퍼 활성화
    glEnable(GL_LIGHTING); // 조명 활성화
    glEnable(GL_LIGHT0); // 0 번 광원 활성화
    glEnable(GL_LIGHT1); // 1 번 광원 활성화
}

struct particle {
    GLfloat px, py, pz;
    GLfloat pr, pg, pb;
    GLfloat pxd, pyd, pzd;
    GLfloat pcs;
} p[1000];

void LoadParticleTexture(void) {
    AUX_RGBImageRec* pTextureImage[4];
    memset(pTextureImage, 0, sizeof(void*) * 4);

    if ((pTextureImage[0] = auxDIBImageLoad("SnowSmall.bmp")) &&
        (pTextureImage[1] = auxDIBImageLoad("SnowMiddle.bmp")) &&
        (pTextureImage[2] = auxDIBImageLoad("SnowLarge.bmp")) &&
        (pTextureImage[3] = auxDIBImageLoad("wLawn.bmp"))) {

        for (int i = 0; i < 4; i++) {
            glGenTextures(1, &p_textureID[i]);
            glBindTexture(GL_TEXTURE_2D, p_textureID[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[i]->sizeX, pTextureImage[i]->sizeY, 0,
                GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[i]->data);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (pTextureImage[i]) {
            if (pTextureImage[i]->data)		free(pTextureImage[i]->data);
            free(pTextureImage[i]);
        }
    }
}

void MyReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glTranslatef(0.0f, 0.0f, g_fDistance);
//    glRotatef(-g_fSpinY, 1.0f, 0.0f, 0.0f);
//    glRotatef(-g_fSpinX, 0.0f, 1.0f, 0.0f);

    glBindTexture(GL_TEXTURE_2D, texture[1]); // 벽과 바닥 texture

    glBegin(GL_QUADS);
    glTexCoord2f(0.5f, 0.0f); glVertex3f(-1.2f, -1.7f, -1.1f);		// 뒷면 - 벽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.7f, -1.7f, -1.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.7f, 1.4f - open, -1.1f - open);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-1.2f, 1.4f - open, -1.1f - open);

    glTexCoord2f(0.5f, 0.0f); glVertex3f(5.7f, -1.7f, 2.4f);		// 우측면 - 벽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.7f, -1.7f, -1.1f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.7f + open, 1.4f - open, -1.1f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(5.7f + open, 1.4f - open, 2.4f);

    glTexCoord2f(0.5f, 0.0f); glVertex3f(-1.2f, -1.7f, -1.1f);	// 좌측면 - 벽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.2f, -1.7f, 2.4f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.2f - open, 1.4f - open, 2.4f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-1.2f - open, 1.4f - open, -1.1f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.2f, -1.7f, -1.1f);		// 아랫면 - 바닥
    glTexCoord2f(0.5f, 0.0f); glVertex3f(5.7f, -1.7f, -1.1f);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(5.7f, -1.7f, 2.4f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.2f, -1.7f, 2.4f);

    glTexCoord2f(0.5f, 0.0f); glVertex3f(-1.2f, 1.4f - Delta, 2.4f);		// 앞면 - 벽
    glTexCoord2f(1.0f, 0.0f); glVertex3f(5.7f, 1.4f - Delta, 2.4f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(5.7f, 4.5f - Delta - open, 2.4f + open);
    glTexCoord2f(0.5f, 1.0f); glVertex3f(-1.2f, 4.5f - Delta - open, 2.4f + open); 
    glEnd();

    glPushMatrix();
        gluQuadricNormals(qobj, GLU_SMOOTH);

        // Snowman
        glPushMatrix();
            // Body
            glBindTexture(GL_TEXTURE_2D, texture[2]);
            glTranslatef(2.3f, -1.4f, 1.0f);
            gluSphere(qobj, 0.3f, 26, 13);

            glTranslatef(0.0f, 0.45f, 0.0f);
            gluSphere(qobj, 0.24f, 26, 13);

            // Eyes
            glBindTexture(GL_TEXTURE_2D, texture[3]);
            glTranslatef(0.1f, 0.1f, 0.21f);
            gluSphere(qobj, 0.02f, 26, 13);
            glTranslatef(-0.2f, 0.0f, 0.0f);
            gluSphere(qobj, 0.02f, 26, 13);

            // Noes
            glBindTexture(GL_TEXTURE_2D, texture[4]);
            glTranslatef(0.1f, -0.12f, 0.0f);
            gluCylinder(qobj, 0.04f, 0.0f, 0.3f, 26, 13);
        glPopMatrix();

        // Hat
        glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[0]);
            glTranslatef(2.3f, -0.77f, 1.0f);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(qobj, 0.17f, 0.17f, 0.4f, 26, 13);

            gluDisk(qobj, 0.17f, 0.28f, 26, 13);

            glTranslatef(0.0f, 0.0f, 0.4f);
            gluDisk(qobj, 0.0f, 0.17f, 26, 13);
        glPopMatrix();
    glPopMatrix();

    // Light
    glPushMatrix();
        if (isLight) {
            glPushMatrix();
                glDisable(GL_LIGHTING);
                glTranslatef(2.25, 2.0, 1.25);
                glutWireCone(0.05, 0.1, 50, 50); // 조명의 위치를 원뿔을 이용해서 보여 줌
                glEnable(GL_LIGHTING);
                MyLightInit();

                glFlush();
            glPopMatrix();
        }
        else {
            glDisable(GL_LIGHTING);
        }
    glPopMatrix();

    // Transparency Mapping - tga
    glPushMatrix();
        if (g_bBlending) {
            glDisable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, g_textureID);
            glInterleavedArrays(GL_T2F_V3F, 0, g_FrontVertices);
            glDrawArrays(GL_QUADS, 0, 24);
        }
        else {
            // Render the front wall, but do no blending...
            glDisable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);

            glBindTexture(GL_TEXTURE_2D, g_textureID);
    //        glInterleavedArrays(GL_T2F_V3F, 0, g_FrontVertices);
    //        glDrawArrays(GL_QUADS, 0, 24);
        }
    glPopMatrix();

    // Environment Mapping
    glPushMatrix();
        if (isEnv) {
            glPushMatrix();
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            glBindTexture(GL_TEXTURE_2D, envtexture[filter + (filter + 1)]);
            glTranslatef(2.30f, 1.0f, 0.0f);
            gluSphere(quadratic, 0.7f, 32, 32);
            glPopMatrix();
        }
        else {
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
        }
    glPopMatrix();

    // Snow
    glPushMatrix();
        if (isSnow) {
            /*    glPushMatrix();
                glColor4ub(255, 255, 255, 255);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glBindTexture(GL_TEXTURE_2D, p_textureID[2]);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -0.5f, 1.0f);
                glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -0.5f, -1.0f);
                glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -0.5f, -1.0f);
                glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -0.5f, 1.0f);
                glEnd();
                glPopMatrix();*/

            glPushMatrix();
            for (int i = 0; i < 1000; i++) {
                p[i].px += cos(winddir * .0174532925f) * windspeed;
                p[i].py += p[i].pyd;
                p[i].pz += sin(winddir * .0174532925f) * windspeed;
                //			p[i].yd	-= rand()/32767.0f/100000.0f;	

                if (p[i].py <= -1.7f) {
                    p[i].pxd = -(rand() / 32767.0f - 0.5f) / 200.0f;
                    p[i].pzd = -(rand() / 32767.0f - 0.5f) / 200.0f;
                    p[i].pyd = -rand() / 32767.0f / 100.0f;
                    p[i].px = (rand() / 32767.0f - 1.0f);
                    p[i].py = 1.0f;
                    p[i].pz = (rand() / 32767.0f - 1.0f);
                    p[i].pb = rand() / 32767.0f;
                    p[i].pg = p[i].pb;
                    p[i].pr = p[i].pb;
                }
            }

            for (int i = 0; i < 1000; i++) {
                float dif = 0.0;
                if (i % 3 == 0)		dif = 0.01;
                else if (i % 3 == 1)	dif = 0.02;
                else				dif = 0.03;
                //			glColor3f(p[i].pr, p[i].pg, p[i].pb);
                glEnable(GL_BLEND);
                glDepthFunc(GL_LEQUAL);
                glBlendFunc(GL_ONE, GL_ONE);
                glBindTexture(GL_TEXTURE_2D, p_textureID[i % 3]);
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f); glVertex3f(2.75f + p[i].px - dif, p[i].py - dif, p[i].pz);
                glTexCoord2f(1.0f, 0.0f); glVertex3f(2.75f + p[i].px, p[i].py - dif, p[i].pz);
                glTexCoord2f(1.0f, 1.0f); glVertex3f(2.75f + p[i].px, p[i].py, p[i].pz);
                glTexCoord2f(0.0f, 1.0f); glVertex3f(2.75f + p[i].px - dif, p[i].py, p[i].pz);
                glEnd();
            }
            glPopMatrix();

            glutPostRedisplay();
        }
    glPopMatrix();

    glutSwapBuffers();
}

int InitGL(void) {
    LoadParticleTexture();

    for (int i = 0; i < 1000; i++) {
        p[i].pxd = -(rand() / 32767.0f - 0.5f) / 200.0f;
        p[i].pzd = -(rand() / 32767.0f - 0.5f) / 200.0f;
        p[i].pyd = -rand() / 32767.0f / 100.0f;
        p[i].px = (rand() / 32767.0f - 1.0f);
        p[i].py = 1.0f;
        p[i].pz = (rand() / 32767.0f - 1.0f);
        p[i].pb = rand() / 32767.0f;
        p[i].pg = p[i].pb;
        p[i].pr = p[i].pb;
    }

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    //    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    return true;
}

AUX_RGBImageRec* LoadBMP(char* Filename) {
    FILE* File = NULL;
    if (!Filename) return NULL;
    File = fopen(Filename, "r");
    if (File) {
        fclose(File);
        return auxDIBImageLoad(Filename);	     // 파일로부터 메모리로
    }
    return NULL;
}

int LoadGLTextures() {                                   // 파일을 로드하고 텍스쳐로 변환
    int Status = TRUE, i;
    AUX_RGBImageRec* TextureImage;
    qobj = gluNewQuadric();
    gluQuadricTexture(qobj, GL_TRUE);

    for (i = 0; i < TEXTURE_NUM; i++) {
        TextureImage = NULL;
        if (TextureImage = LoadBMP(texture_name[i])) {
            glGenTextures(1, &texture[i]);
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage->sizeX, TextureImage->sizeY,
                0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
        }
        else {
            MessageBox(NULL, "Image file has a error !", texture_name[i], MB_ICONERROR);
            Status = false;
        }

        if (TextureImage) {
            if (TextureImage->data) free(TextureImage->data);
            free(TextureImage);
        }
    }
    return Status;
}

void LoadEnvTextures() {
    AUX_RGBImageRec* EnvTextureImage[2];
    memset(EnvTextureImage, 0, sizeof(void*) * 2);

    if ((EnvTextureImage[0] = LoadBMP((char*)"Background.bmp")) && // 형 변환
        (EnvTextureImage[1] = LoadBMP((char*)"SphereMap.bmp"))) {
        glGenTextures(6, &envtexture[0]);

        for (int i = 0; i < 2; i++) {
            // Create Nearest Filtered Texture
            glBindTexture(GL_TEXTURE_2D, envtexture[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, EnvTextureImage[i]->sizeX,
                EnvTextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
                EnvTextureImage[i]->data);

            // Create Linear Filtered Texture
            glBindTexture(GL_TEXTURE_2D, envtexture[i + 2]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, 3, EnvTextureImage[i]->sizeX,
                EnvTextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
                EnvTextureImage[i]->data);

            // Create MipMapped Texture
            glBindTexture(GL_TEXTURE_2D, envtexture[i + 4]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_NEAREST);
            gluBuild2DMipmaps(GL_TEXTURE_2D, 3, EnvTextureImage[i]->sizeX,
                EnvTextureImage[i]->sizeY, GL_RGB, GL_UNSIGNED_BYTE,
                EnvTextureImage[i]->data);
        }

        for (int i = 0; i < 2; i++) {
            if (EnvTextureImage[i]) {
                if (EnvTextureImage[i]->data) {
                    free(EnvTextureImage[i]->data);
                }
                free(EnvTextureImage[i]);
            }
        }
    }
}

void InitEnv() {
    GLfloat Light0_Ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat Light0_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat Light0_Position[] = { 0.0f, 0.0f, 2.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);

    LoadEnvTextures();

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    quadratic = gluNewQuadric();
    gluQuadricNormals(quadratic, GLU_SMOOTH);
    gluQuadricTexture(quadratic, GL_TRUE);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

void MyMouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON: // Animation Play
        isTime = true;
        break;
    case GLUT_RIGHT_BUTTON: // Animation Pause
        isTime = false;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void MySpecial(int key, int kx, int ky) { // 카메라 시점 이동

//    float fraction = 0.1f;

    switch (key) {
    case GLUT_KEY_DOWN: // 아래방향 화살표 // 카메라 아래로 이동
        y -= 0.1f; 
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case GLUT_KEY_UP:   // 위방향 화살표 // 카메라 위로 이동
        y += 0.1f; 
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case GLUT_KEY_LEFT: // 왼쪽방향 화살표 // 카메라 왼쪽 이동
        x -= 0.1f;
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case GLUT_KEY_RIGHT:// 오른쪽방향 화살표 // 카메라 오른쪽 이동
        x += 0.1f;
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case GLUT_KEY_PAGE_UP: // PgUp // 카메라 Zoom In
        if (z >= 9.5) { // 제약 조건
            x += lx * fraction;
            z += lz * fraction;
            glLoadIdentity();
            gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        }
        break;

    case GLUT_KEY_PAGE_DOWN: // PgDn // 카메라 Zoom Out
        if (z <= 30) { // 제약 조건
            x -= lx * fraction;
            z -= lz * fraction;
            glLoadIdentity();
            gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        }
        break;
    }
    glutPostRedisplay(); // MyDisplay(); 호출
}

void MyKeyboard(unsigned char key, int kx, int ky) {
    switch (key) {
    case 'w': // 카메라 위로 회전
        angle += 0.01f;
        ly = sin(angle);
        lz = -cos(angle);
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case 's': // 카메라 아래로 회전
        angle -= 0.01f;
        ly = sin(angle);
        lz = -cos(angle);
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case 'a': // 카메라 왼쪽으로 회전
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;

    case 'd': // 카메라 오른쪽으로 회전
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        glLoadIdentity();
        gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
        break;
    }
    glutPostRedisplay();
}

void MyTimer(int Value) { // 타이머로 애니메이션 효과 주기
    if (isTime) {
        if (Delta <= 3.0f) {
            Delta += 0.1f;
            g_bBlending = false;
            isLight = false;
            isSnow = false;
        }
        if (Delta > 3.0f) {
            if (open < 3.0f) open += 0.1f;
            else {
                g_bBlending = true;
                wait += 0.1f;
                isSnow = false;
            }
        }

        if (wait > 1.0f) {
            wait += 0.1f;
            isLight = true;

            if (wait > 2.5f) {
                isLight = false;
                wait += 0.1f;

                if (wait > 3.5f) {
                    g_bBlending = false;
                    wait += 0.1f;

                    if (wait > 6.5f) {
                        isEnv = true;
                        wait += 0.1f;

                        if (wait > 9.5f) {
                            isEnv = false;
                            isSnow = true;
                            wait += 0.1f;

                            if (wait > 105.f) {
                                isSnow = false;
                                wait += 0.1f;

                                if (wait > 107.f) {
                                    Delta = 0.0f;
                                    open = 0.0f;
                                    wait = 0.0f;
                                }
                            }
                        }
                    }
                }
            }
        } 
    }
    glutPostRedisplay();
    glutTimerFunc(40, MyTimer, 1);
}


void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(1024, 768); // Window의 해상도 1024×768로 설정
    glutCreateWindow("Final_Project");

    glutSpecialFunc(MySpecial); // 카메라 시점 이동 등록
    glutKeyboardFunc(MyKeyboard); // 카메라 회전 등록

    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);

    glutTimerFunc(40, MyTimer, 1);  // 40msec
    glutMouseFunc(MyMouse);

    LoadGLTextures();
    loadTexture();

    InitGL();
    InitEnv();

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutMainLoop();
}