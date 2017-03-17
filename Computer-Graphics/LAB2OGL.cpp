//
//  LAB2OGL.cpp
//  OpenGL Tests
//
//  Created by Kamil Kosiński on 13/12/2016.
//  Copyright © 2016 Kamil Kosiński. All rights reserved.
//

//#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<OpenGL/gl.h>
#include<GLUT/glut.h>

void TimerFunction(int);
void KeyboardFunc(unsigned char, int, int);
void DrawScene(void);
void DrawSceneAxes(void);
void InitOpenGL(void);
void ReshapeWindow(int width, int height);

int mainWindow;
GLfloat x_angle=0.0f; //ZADANIE 6
GLfloat y_angle=0.0f; //ZADANIE 6
GLfloat v_angle=0.0f; //ZADANIE 10

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(150,150);
    mainWindow = glutCreateWindow("Transformacje czajnikowe");
    
    if(mainWindow == 0){
        puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
        exit(-1);
    }
    
    glutSetWindow(mainWindow);
    
    glutDisplayFunc(DrawScene);
    glutReshapeFunc(ReshapeWindow);
    glutKeyboardFunc(KeyboardFunc); //ZADANIE 9
    
    InitOpenGL();
    
    glEnable(GL_DEPTH_TEST);
    
    TimerFunction(0);
    
    glutMainLoop();
    
    return(0);
}

void TimerFunction(int val) //ZADANIE 8
{
    /*ZADANIE 8
    x_angle+=0.05f;
    y_angle+=0.05f;
        
    glRotatef(x_angle, 1.0f, 0.0f, 0.0f);
    glRotatef(y_angle, 0.0f, 1.0f, 0.0f);*/
    
    glRotatef(v_angle, 1.0f, 1.0f, 0.0f); //ZADANIE 10
        
    glutPostRedisplay();
    glutTimerFunc(20, TimerFunction, 0);
}

void KeyboardFunc(unsigned char key, int x, int y) //ZADANIE 10
{
    switch(key)
    {
        case  27:
            exit(0);
        case 'w':
            v_angle += 0.05f;
            break;
        case 'r':
            v_angle -= 0.05f;
            break;
    }
    
    glutPostRedisplay();
}

void DrawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    DrawSceneAxes();
    
    //glRotatef(-20.0f, 1.0f, 0.3f, 0.0f); //ZADANIE 4
    
    glutWireTeapot(4.0); //ZADANIE 2
    
    //glTranslatef(2.0f, 2.5f, 2.0f); //ZADANIE 5
    //glScalef(1.5f, 1.25f, 1.0f); //ZADANIE 5

    //glRotatef(x_angle, 1.0f, 0.0f, 0.0f); //ZADANIE 7
    //glRotatef(y_angle, 0.0f, 1.0f, 0.0f); //ZADANIE 7
    
    glutSwapBuffers();
}

void DrawSceneAxes(void)
{
    typedef float pt3d[3];

    pt3d x_beg = { -10.0f, 0.0f, 0.0f };
    pt3d x_end = {  10.0f, 0.0f, 0.0f };
    
    pt3d y_beg = { 0.0f, -10.0f, 0.0f };
    pt3d y_end = { 0.0f,  10.0f, 0.0f };
    
    pt3d z_beg = { 0.0f, 0.0f, -10.0f };
    pt3d z_end = { 0.0f, 0.0f,  10.0f };
    
    glBegin(GL_LINES);
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(x_beg);
    glVertex3fv(x_end);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3fv(y_beg);
    glVertex3fv(y_end);
    
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(z_beg);
    glVertex3fv(z_end);
    
    glEnd();
    
    glColor3f(0.5f, 0.5f, 0.5f); // ZADANIE 2
}

void InitOpenGL(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void ReshapeWindow(int width, int height)
{
    GLdouble nRange = 15.0f;

    if(height == 0)
    {
        height = 1;
    }
    
    if(width == 0)
    {
        width = 1;
    }
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    if(width <= height)
        glOrtho(-nRange, nRange, -nRange*((GLdouble)height / width), nRange*((GLdouble)height / width), -5.0f, 5.0f); //ZADANIE 3
    else
        glOrtho(-nRange*((GLdouble)width / height), nRange*((GLdouble)width / height), -nRange, nRange, -5.0f, 5.0f); //ZADANIE 3
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
}
