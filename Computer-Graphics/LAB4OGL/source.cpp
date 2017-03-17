//
//  LAB3OGL.cpp
//  OpenGL Tests
//
//  Created by Kamil Kosiński on 27/12/2016.
//  Copyright © 2016 Kamil Kosiński. All rights reserved.
//

//#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<OpenGL/gl.h>
#include<GLUT/glut.h>


void DrawScene(void);
//void DrawSceneAxes(void);
void DrawPyramid(void);
void MouseMotion(GLsizei x, GLsizei y);
void MouseFunc(int button, int state, int x, int y);
void KeyboardFunc(unsigned char key, int x, int y);

void InitOpenGL(void);
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
void ReshapeWindow(int width, int height);
GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat);
void LoadTexture(char *nazwa);

GLfloat theta = 0.0f;
GLfloat alpha = 0.0f;

GLdouble size = 2.5;

GLfloat pixels2angle = 0.0;

GLint lbutton_status = 0;
GLint rbutton_status = 0;

GLint x_last_pos = 0;
GLint x_delta = 0;

GLint y_last_pos = 0;
GLint y_delta = 0;

GLfloat R =10;

GLboolean WallSwitch[5]={true, true, true, true, true};

GLfloat viewer_pos[] = { 0.0, 0.0, 10.0 };

int mainWindow;

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(150,150);
    mainWindow = glutCreateWindow("Pyramid");
    
    if(mainWindow == 0){
        puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
        exit(-1);
    }
    glutSetWindow(mainWindow);
    
    glutDisplayFunc(DrawScene);
    glutReshapeFunc(ReshapeWindow);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MouseMotion);
    glutKeyboardFunc(KeyboardFunc);
    
    InitOpenGL();
    
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    
    return(0);
}

void MouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        x_last_pos = x;
        y_last_pos = y;
        lbutton_status = 1;
    }
    else
    {
        lbutton_status = 0;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        y_last_pos = y;
        rbutton_status = 1;
    }
    else
    {
        rbutton_status = 0;
    }
}

void MouseMotion(GLsizei x, GLsizei y)
{
    x_delta = x - x_last_pos;
    x_last_pos = x;
    
    y_delta = y - y_last_pos;
    y_last_pos = y;
    
    glutPostRedisplay();
}

void KeyboardFunc(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1':
            WallSwitch[1]=!WallSwitch[1];
            break;
        case '2':
            WallSwitch[2]=!WallSwitch[2];
            break;
        case '3':
            WallSwitch[3]=!WallSwitch[3];
            break;
        case '4':
            WallSwitch[4]=!WallSwitch[4];
            break;
        case '5':
            WallSwitch[0]=!WallSwitch[0];
            break;
    }
    
    glutPostRedisplay();
}

void DrawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    gluLookAt(viewer_pos[0],viewer_pos[1],viewer_pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    //DrawSceneAxes();
    
    //glColor3f(1.0f, 1.0f, 1.0f);
    
    if(lbutton_status == 1)
    {
        theta += x_delta*pixels2angle;//50;
        alpha += y_delta*pixels2angle;//50;
        
        //viewer_pos[0] = R * cos(theta) * cos(alpha);
        //viewer_pos[1] = R * sin(theta);
        //viewer_pos[2] = R * cos(theta) * sin(alpha);
    }
    glRotatef(theta, 0.0f, 1.0f, 0.0f);
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    
    if(rbutton_status == 1)
    {
        if(y_delta>0||size>0)
            size += y_delta*0.01;
        if(size<0) size=0;
    }
    
    //glutSolidTeapot(size);
    
    DrawPyramid();
    
    glutSwapBuffers();
    
}

void DrawPyramid(void)
{
    for(int i=0; i<5; i++)
    {
        if(WallSwitch[i]==true)
        {
            if(i==0)
            {
                LoadTexture("D2_t.tga");
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f);
                glVertex3f(-size, -size, size);
                glTexCoord2f(1.0f, 1.0f);
                glVertex3f(size, -size, size);
                glTexCoord2f(1.0f, 0.0f);
                glVertex3f(size, -size, -size);
                glTexCoord2f(0.0f, 0.0f);
                glVertex3f(-size, -size, -size);
                glEnd();
                LoadTexture("D9_t.tga");
                continue;
            }
            
            glBegin(GL_TRIANGLES);
            glTexCoord2f(0.0f, 0.0f);
            switch(i)
            {
                case 1:
                    glVertex3f(-size, -size, size);
                    break;
                case 2:
                    glVertex3f(size, -size, size);
                    break;
                case 3:
                    glVertex3f(size, -size, -size);
                    break;
                case 4:
                    glVertex3f(-size, -size, -size);
                    break;
            }
            glTexCoord2f(0.5f, 1.0f);
            glVertex3f(0, size, 0);
            glTexCoord2f(1.0f, 0.0f);
            switch(i)
            {
                case 1:
                    glVertex3f(size, -size, size);
                    break;
                case 2:
                    glVertex3f(size, -size, -size);
                    break;
                case 3:
                    glVertex3f(-size, -size, -size);
                    break;
                case 4:
                    glVertex3f(-size, -size, size);
                    break;
            }
            glEnd();
        }
    }
}

void InitOpenGL(void)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    
    GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess = {20.0};
    
    GLfloat light_position[] = {0.0, 0.0, 10.0, 1.0};
    GLfloat light_ambient[] = {0.1, 0.1, 0.1, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[]= {1.0, 1.0, 1.0, 1.0};
    
    GLfloat att_constant = {1.0};
    GLfloat att_linear = {0.05};
    GLfloat att_quadratic = {0.001};
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void ReshapeWindow(int width, int height)
{
    pixels2angle = 360.0f/(float)width;
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    perspectiveGL(70.0, 1.0, 1.0, 20.0);
    
    if(width <= height)
        glViewport(0, (height - width)/2, width, width);
    else
        glViewport((width - height)/2, 0, height, height);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
}

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{
    // Struktura dla nagłówka pliku TGA
    #pragma pack(1) 
    
    typedef struct
    {
        GLbyte idlength;
        GLbyte colormaptype;
        GLbyte datatypecode;
        unsigned short colormapstart;
        unsigned short colormaplength;
        unsigned char colormapdepth;
        unsigned short x_orgin;
        unsigned short y_orgin;
        unsigned short width;
        unsigned short height;
        GLbyte bitsperpixel;
        GLbyte descriptor;
    }TGAHEADER;
    
    #pragma pack(8)
    
    FILE *pFile;
    TGAHEADER tgaHeader;
    unsigned long lImageSize;
    short sDepth;
    GLbyte *pbitsperpixel = NULL;
    
    *ImWidth = 0;
    *ImHeight = 0;
    *ImFormat = GL_BGR_EXT;
    *ImComponents = GL_RGB8;
    
    pFile = fopen(FileName, "rb");
    if(pFile == NULL)
        return NULL;
    
    fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);
    *ImWidth = tgaHeader.width;
    *ImHeight = tgaHeader.height;
    sDepth = tgaHeader.bitsperpixel/8;
    
    if(tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
        return NULL;
    
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pbitsperpixel == NULL)
        return NULL;
    
    if(fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
    {
        free(pbitsperpixel);
        return NULL;
    }
    
    switch(sDepth)
    {
        case 3:
            *ImFormat = GL_BGR_EXT;
            *ImComponents = GL_RGB8;
            break;
        case 4:
            *ImFormat = GL_BGRA_EXT;
            *ImComponents = GL_RGBA8;
            break;
        case 1:
            *ImFormat = GL_LUMINANCE;
            *ImComponents = GL_LUMINANCE8;
            break;
    };
    
    fclose(pFile);
    return pbitsperpixel;
}

void LoadTexture(char *nazwa)
{
    GLbyte *pBytes;
    GLint ImWidth, ImHeight, ImComponents;
    GLenum ImFormat;
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    pBytes = LoadTGAImage(nazwa, &ImWidth, &ImHeight, &ImComponents, &ImFormat);
    
    glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
    
    free(pBytes);
    
    glEnable(GL_TEXTURE_2D);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

