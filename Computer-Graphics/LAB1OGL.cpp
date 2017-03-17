//
//  main.cpp
//  OpenGL Tests
//
//  Created by Kamil Kosiński on 06/12/2016.
//  Copyright © 2016 Kamil Kosiński. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <ctime>

using namespace std;

void DrawScene(void);
void DrawLayer(float*, float);
void DrawSquare(float*, float);
void setMiddlePoints(float*, float**, float);
void InitOpenGL(void);
void ReshapeWindow(int width, int height);

int mainWindow;
int timesAmount;
const int windowSize=900;

int main(int argc, char **argv)
{
    cout<<"Input amount of fractal layers (between 0 and 5): ";
    cin>>timesAmount;
    
    while(timesAmount<0||timesAmount>5)
    {
        cout<<"Wrong input. Retry: ";
        cin>>timesAmount;
    }
    
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    
    glutInitWindowSize(windowSize, windowSize);
    
    glutInitWindowPosition(150,150);
    
    char windowName[28];
    sprintf(windowName, "Sierpinski carpet: %1d layers", timesAmount);
    
    mainWindow = glutCreateWindow(windowName);
    
    if(mainWindow == 0){
        puts("Cannot create window!\nExiting...\n");
        exit(-1);
    }
    
    cout<<glGetString(GL_VERSION);
    
    glutSetWindow(mainWindow);
    
    glutDisplayFunc(DrawScene);
    glutReshapeFunc(ReshapeWindow);
    
    InitOpenGL();
    
    glutMainLoop();
    
    return(0);
}

void DrawScene(void)
{
    clock_t begin=clock();
    float size=(windowSize/9);
    float middlePoint[2]={0, 0};
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    
    //DrawSquare(middlePoint, size, color);
    
    DrawLayer(middlePoint, size);
    
    glFlush();
    
    //cout<<clock()-begin<<endl;
}

void DrawLayer(float *middlePoint, float size)
{
    size/=3;
    
    DrawSquare(middlePoint, size);
    
    if(timesAmount>0)
    {
        timesAmount--;
        
        float **middlePointGroup = new float*[8];
        for(int i=0; i<8; i++)
            middlePointGroup[i] = new float[2];
        
        setMiddlePoints(middlePoint, middlePointGroup, size);
        
        for(int i=0; i<8; i++)
        {
            DrawLayer(middlePointGroup[i], size);
            delete [] middlePointGroup[i];
        }
        
        delete [] middlePointGroup;
        
        timesAmount++;
    }
}

void DrawSquare(float *middlePoint, float size)
{
    glBegin(GL_POLYGON);
    
    glVertex2f(middlePoint[0]-size, middlePoint[1]-size);
    
    glVertex2f(middlePoint[0]-size, middlePoint[1]+size);
    
    glVertex2f(middlePoint[0]+size, middlePoint[1]+size);
    
    glVertex2f(middlePoint[0]+size, middlePoint[1]-size);
    
    glEnd();
    
    glFlush();
}

void setMiddlePoints(float *middlePoint, float **middlePointGroup, float size)
{
     middlePointGroup[0][0]=middlePoint[0]-(2*size);
     middlePointGroup[0][1]=middlePoint[1]+(2*size);
     
     middlePointGroup[1][0]=middlePoint[0];
     middlePointGroup[1][1]=middlePoint[1]+(2*size);
     
     middlePointGroup[2][0]=middlePoint[0]+(2*size);
     middlePointGroup[2][1]=middlePoint[1]+(2*size);
     
     middlePointGroup[3][0]=middlePoint[0]-(2*size);
     middlePointGroup[3][1]=middlePoint[1];
     
     middlePointGroup[4][0]=middlePoint[0]+(2*size);
     middlePointGroup[4][1]=middlePoint[1];
     
     middlePointGroup[5][0]=middlePoint[0]-(2*size);
     middlePointGroup[5][1]=middlePoint[1]-(2*size);
     
     middlePointGroup[6][0]=middlePoint[0];
     middlePointGroup[6][1]=middlePoint[1]-(2*size);
     
     middlePointGroup[7][0]=middlePoint[0]+(2*size);
     middlePointGroup[7][1]=middlePoint[1]-(2*size);
}

void InitOpenGL(void)
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void ReshapeWindow(int width, int height)
{
    int aspectRatio;
    if(height == 0) height = 1;
    aspectRatio = width / height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if(width <= height)
        glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
