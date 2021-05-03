#include "ringue.h"
#include <math.h>


void Ringue::DefineTamanhoLadoTotal()
{
    GLfloat x1 = gMesh.vertsPos[pontoBase1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBase1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBase2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBase2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    ladoTotal = (int)distanciaPontos;

}


void Ringue::DefineTamanhoLado()
{
    GLfloat x1 = gMesh.vertsPos[pontoBaseInterno1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBaseInterno1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBaseInterno2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBaseInterno2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    lado = (int)distanciaPontos;

}

void Ringue::DesenhaRingue()
{
    glPushMatrix();
            glTranslatef(0, 0, -profundidade);

        glScalef(gProporcao, gProporcao, gProporcao);
        gMesh.draw();
    glPopMatrix();

}

