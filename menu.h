#ifndef MENU_H
#define	MENU_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "tinyxml/tinyxml.h"

using namespace std;

class Menu
{
    GLfloat gX;
    GLfloat gY;
    void * fonte = GLUT_BITMAP_8_BY_13;
    void PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b);
    void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b);

private:
    void DesenhaTexto(GLfloat x, GLfloat y, char texto[1000], bool center);
public:
    Menu(){}

    void Iniciacao(GLfloat x, GLfloat y)
    {
        gX = x;
        gY = y;
    }

    void DesenhaPlacar(GLint pontosLutador, GLint pontosBot);
    void DesenhaFinalJogo(bool ganhou);
    void DesenhaMenu();
};

#endif	/* MENU_H */
