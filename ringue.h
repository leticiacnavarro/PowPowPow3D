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

#define pontoCanto1 1436
#define pontoCanto2 48
#define pontoCanto3 742
#define pontoCanto4 2128


#include "objloader.h"
#include "imageloader.h"

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

    GLuint LoadTextureRAW( const char * filename );

    void DefineAltura();

public:
    //Tamanho
    int lado;
    int ladoTotal;
    GLfloat altura;

    Ringue()
    {
        gMesh.loadMesh("modelos/ringueNew.obj");
        DefineTamanhoLado();
        DefineTamanhoLadoTotal();
        DefineAltura();
    }

    void Iniciacao(GLfloat x, GLfloat y){

        gProporcao = x/lado;
    };

    void Desenha(){
        DesenhaRingue();
    }
    GLfloat LadoColisao();

    void CarregaTexturas();
    
    GLfloat GetXMeshPuro(GLfloat meshpoint);

    GLfloat GetYMeshPuro(GLfloat meshpoint);

    GLfloat GetZMeshPuro(GLfloat meshpoint);
    

};

#endif	/* RINGUE_H */
