#ifndef RINGUE_H
#define	RINGUE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

using namespace std;

#define thetaInicial1 135
#define thetaInicial2 225

using namespace std;

#include "objloader.h"

class Ringue
{
    //Posições
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;

    //3d
    mesh gMesh;

    //Proporcao
    GLfloat gProporcao;

private:
    void DesenhaRingue();

public:

    Ringue(){
    }

    void Iniciacao(GLfloat x, GLfloat y, GLfloat proporcao){
        
        gX = x/2;
        gY = y/2;
        gZ = x/2;

        gProporcao = gX/2;
      //  gMesh.loadMesh("modelos/ringue.obj");
        gMesh.loadMesh("modelos/ringueBonito.obj");

    };

    void Desenha(){
        DesenhaRingue();
    }

};

#endif	/* RINGUE_H */
