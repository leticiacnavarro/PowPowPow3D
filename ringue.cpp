#include "ringue.h"
#include <math.h>

// void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
// {
//     int pts = 50;
//     glColor3f (R, G, B);

//     for(unsigned int i = 0; i <= pts; ++i ){

//         float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
//         float x = radius * sin(angle);
//         float y = radius * cos(angle);
        
//         glPointSize(3);

//         glBegin(GL_POLYGON);
//             glVertex3f(x, y, 0.0f);
//     }
//     glEnd();
// }

void Ringue::DefineTamanhoLado()
{
    GLfloat x1 = gMesh.vertsPos[pontoBase1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBase1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBase2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBase2].y;

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

