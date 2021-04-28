#ifndef MENU_H
#define	MENU_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ringue.h"

using namespace std;

class Menu
{
    GLfloat gX;
    GLfloat gY;

    GLfloat gXLutador;
    GLfloat gYLutador;

    GLfloat gXBot;
    GLfloat gYBot;
    
    void * fonte = GLUT_BITMAP_8_BY_13;


private:
    void DesenhaTexto(GLfloat x, GLfloat y, char texto[1000], bool center);
    void DesenhaMiniArena(GLfloat side, double r, double g, double b);
    void PrintText(GLfloat x, GLfloat y, const char * text, double r, double g, double b);
    void RasterChars(GLfloat x, GLfloat y, GLfloat z, const char * text, double r, double g, double b);
    void PrintDrawing(GLfloat x, GLfloat y, double r, double g, double b);
    void RasterRectangle(GLfloat x, GLfloat y, GLfloat z, double r, double g, double b);
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void RasterCircle(GLfloat x, GLfloat y, GLfloat z, double r, double g, double b);
    void CalculaPosicao(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

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
    void DesenhaMiniMapa(GLfloat xLutador, GLfloat yLutador, GLfloat xBot, GLfloat yBot);
};

#endif	/* MENU_H */
