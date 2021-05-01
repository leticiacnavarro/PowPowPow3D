#ifndef RINGUE_H
#define	RINGUE_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

using namespace std;

#define pontoBase1 1972
#define pontoBase2 2758

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

public:
    //Tamanho
    int lado;
    Ringue()
    {
        gMesh.loadMesh("modelos/boxingRing.obj");
        DefineTamanhoLado();
    }

    void Iniciacao(GLfloat x, GLfloat y){
        
        gProporcao = x/lado;
        cout << gProporcao << endl;

    };

    void Desenha(){
        DesenhaRingue();
    }

};

#endif	/* RINGUE_H */
