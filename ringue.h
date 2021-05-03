#ifndef RINGUE_H
#define	RINGUE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

using namespace std;

#define pontoBaseInterno1 1972
#define pontoBaseInterno2 2758

#define pontoBase1 1391
#define pontoBase2 2085

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

    void DefineTamanhoLado();
    
    void DefineTamanhoLadoTotal();


public:
    //Tamanho
    int lado;
    int ladoTotal;

    Ringue()
    {
        gMesh.loadMesh("modelos/boxingRing.obj");
        DefineTamanhoLado();
        DefineTamanhoLadoTotal();
    }

    void Iniciacao(GLfloat x, GLfloat y){

        gProporcao = x/lado;
    };

    void Desenha(){
        DesenhaRingue();
    }
    GLfloat LadoColisao();

};

#endif	/* RINGUE_H */
