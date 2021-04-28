#ifndef RINGUE_H
#define	RINGUE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

using namespace std;

#define thetaInicial1 135
#define thetaInicial2 225

#define ladoRingue 180
#define profundidade 60
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
        
    gMesh.loadMesh("modelos/ringue.obj");

    };

    void Desenha(){
        DesenhaRingue();
    }

};

#endif	/* RINGUE_H */
