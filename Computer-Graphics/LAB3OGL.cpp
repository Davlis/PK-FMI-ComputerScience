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


/* Deklaracje funkcji narzêdziowych */

/* Funkcja do rysowania */
void DrawScene(void);
/* Prototyp fukcji rysuj¹cej osie uk³¹du */
void DrawSceneAxes(void);
void MouseMotion(GLsizei x, GLsizei y);
void MouseFunc(int button, int state, int x, int y);


/* Funkcja do inicjacji OpenGLa */
void InitOpenGL(void);

/* Funkcja wywo³ywana w momentach zmiany rozmiarów okna */
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
void ReshapeWindow(int width, int height);

/* Deklaracja globalnych zmiennych */
/* Kąt obrotu czajnika */
GLfloat theta = 0.0f;
GLfloat alpha = 0.0f;

GLdouble size = 4.0;

GLfloat pixels2angle = 0.0;

GLint lbutton_status = 0;
GLint rbutton_status = 0;

GLint x_last_pos = 0;
GLint x_delta = 0;

GLint y_last_pos = 0;
GLint y_delta = 0;

GLfloat R =10;

/* Pozycja obserwatora */
GLfloat viewer_pos[] = { 0.0, 0.0, 10.0 };

/* Globalny identyfikator g³ównego okna programu */
int mainWindow;

/* Funkcja main */
int main(int argc, char **argv)
{
    // Inicjujemy bibliotekê GLUT
    glutInit(&argc, argv);
    // Inicjujemy: format koloru, dwa bufoy ramki
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // Ustawiamy pocz¹tkowe wymiary okna
    glutInitWindowSize(900, 900);
    // Ustawiamy pozycjê okna - lewy górny naro¿nik
    glutInitWindowPosition(150,150);
    // Tworzymy g³ówne okno programu
    mainWindow = glutCreateWindow("Transformacje czajnikowe");
    
    // Sprawdzamy powodzenie operacji
    if(mainWindow == 0){
        puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
        exit(-1);
    }
    // Czynimy aktywnym okno g³ówne programu
    glutSetWindow(mainWindow);
    
    // Tutaj rejestrujemy funkcje narzêdziowe - tzw. callbacks
    glutDisplayFunc(DrawScene);
    glutReshapeFunc(ReshapeWindow);
    // Rejestracja funkcji odpowiedzialnej stan myszy
    glutMouseFunc(MouseFunc);
    // Rejestracja funkcji odpowiedzialnej za ruch myszy
    glutMotionFunc(MouseMotion);
    
    // Ustawienia pocz¹tkowe
    InitOpenGL();
    
    // W³¹czamy mechanizm usuwania niewidocznych powierzchni
    glEnable(GL_DEPTH_TEST);
    
    // Wejœcie do pêtli programu
    glutMainLoop();
    
    return(0);
}

void MouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Zapamętujemy obecne położenie myszy
        x_last_pos = x;
        y_last_pos = y;
        // Przycisk lewy wcisnięty
        lbutton_status = 1;
    }
    else
    {
        // Przycisk jest zwolniony
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

/* Funkcja monitoruje położenie myszy i ustala odpowiednie zmienne */
void MouseMotion(GLsizei x, GLsizei y)
{
    // Wyliczamy aktualne przemieszczenie
    x_delta = x - x_last_pos;
    // Zapamiętujemy aktualne położenie
    x_last_pos = x;
    
    y_delta = y - y_last_pos;
    y_last_pos = y;
    
    // Odświeżamy okno
    glutPostRedisplay();
}


/* W tej funkcji okreœlamy to co ma byc narysowane na ekranie.
 * Jest wywo³ywana zawsze wtedy, gdy trzeba przerysowaæ ekran - bufor ramki.
 */
void DrawScene(void)
{
    // Czyœcimy okno aktualnym (domyœlnym) kolorem oraz resetujemy bufor g³êbi
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Resetujemy bie¿¹c¹ macierz
    glLoadIdentity();
    
    // Definiujemy po³o¿enie obserwatora
    gluLookAt(viewer_pos[0],viewer_pos[1],viewer_pos[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Rysujemy osie uk³adu
    DrawSceneAxes();
    
    // Zamieniamy bufory ramki
    glutSwapBuffers();
    
}

/* Ta funkcja jest wywo³ywana przez funkcjê DrawScene.
 * Jej zadaniem jest rysowanie konkretnych obiektów osi uk³adu
 * wspó³rzêdnych.
 */
void DrawSceneAxes(void)
{
    // Definiujemy nowy typ jako tablicê 3-elementow¹
    typedef float pt3d[3];
    
    // Pocz¹tek i koniec osi X
    pt3d x_beg = { -10.0f, 0.0f, 0.0f };
    pt3d x_end = {  10.0f, 0.0f, 0.0f };
    
    // Poczatek i koniec osi Y
    pt3d y_beg = { 0.0f, -10.0f, 0.0f };
    pt3d y_end = { 0.0f,  10.0f, 0.0f };
    
    // Pocz¹tek i koniec osi Z
    pt3d z_beg = { 0.0f, 0.0f, -10.0f };
    pt3d z_end = { 0.0f, 0.0f,  10.0f };
    
    // Rysujemy osie
    glBegin(GL_LINES);
    // Czerwony kolor dla osi X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(x_beg);
    glVertex3fv(x_end);
    
    // Zielony kolor dla osi Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3fv(y_beg);
    glVertex3fv(y_end);
    
    // Niebieski kolor dla osi Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(z_beg);
    glVertex3fv(z_end);
    glEnd();
    
    glColor3f(0.5f, 0.5f, 0.5f);
    
    
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
    
    glutWireTeapot(size);
}

/* Ta funkcja s³u¿y do wstêpnej konfiguracji OpenGLa.
 * Zanim coœ narysujemy musimy wywo³aæ tê funkcjê.
 */
void InitOpenGL(void)
{
    // Ustawiamy domyœlny, czarny kolor t³a okna - bufor ramki malujemy na czarno
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/*Ta funkcja ustawia perspektywê - jej odpowiednikiem w starszych implementacjach openGL jest gluPerspective
 */
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

/* Tê funkcjê wywo³uje system w momencie gdy u¿ytkownik zmieni mysz¹
 * rozmiar g³ównego okna. jej zadaniem jest zachowanie proporcji wymiarów
 * rysowanych obiektów niezale¿nie od wymiarów okna.
 */
void ReshapeWindow(int width, int height)
{
    // Przeliczamy piksele na stopnie
    pixels2angle = 360.0f/(float)width;
    
    // Ustawiamy uk³ad wspó³rzêdnych obserwatora
    glMatrixMode(GL_PROJECTION);
    
    // Resetujemy macierz projkecji
    glLoadIdentity();
    
    // Ustawiamy perspektywê
    perspectiveGL(70.0, 1.0, 1.0, 20.0);
    
    // Korekta  
    if(width <= height)
        glViewport(0, (height - width)/2, width, width);  
    else
        glViewport((width - height)/2, 0, height, height); 
    
    // Ustawiamy macierz modelu
    glMatrixMode(GL_MODELVIEW);
    
    // Resetujemy macierz modelu
    glLoadIdentity();
    
}

