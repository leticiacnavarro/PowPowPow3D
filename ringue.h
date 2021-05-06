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

#define pontoCanto1 1436
#define pontoCanto2 48
#define pontoCanto3 742
#define pontoCanto4 2128

#define pontoHaste1 2102
#define pontoHaste2 2103


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
    GLfloat gProporcaoAltura;



private:
    void DesenhaRingue();

    void DefineTamanhoLado();
    
    void DefineTamanhoLadoTotal();

    GLuint LoadTextureRAW( const char * filename );

    void DefineAltura();

    void DefineProfundidade();

    GLuint texture;

public:
    //Tamanho
    int lado;
    int ladoTotal;
    GLfloat altura;
    GLfloat profundidade;


    Ringue()
    {
        gMesh.loadMesh("modelos/ringueNew.obj");
        DefineTamanhoLado();

        DefineTamanhoLadoTotal();

        DefineAltura();

        DefineProfundidade();

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
    
    void CalculaAlturaComBaseNoLutador(GLfloat alturaLutador);
};

#endif	/* RINGUE_H */
