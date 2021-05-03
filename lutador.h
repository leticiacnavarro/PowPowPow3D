#ifndef LUTADOR_H
#define	LUTADOR_H
#include <GL/gl.h>
#include <GL/glu.h>
#include <array>
#include <iostream>

#include "objloader.h"
#include "imageloader.h"

using namespace std;

#define thetaInicial1 135
#define thetaInicial2 225

#define raioColisao 10

#define pontoOlho 2833
#define pontoBraco 1833
#define pontoBarriga 1882
#define pontoCabecaAtras 195

#define pontoMaoDireita 2168
#define pontoPulsoDireito 2047

#define pontoMaoEsquerda 3461
#define pontoPulsoEsquerdo 3530

#define pontoMeioCabeca 649

#define pontoPeEsquerdo 1024
#define pontoPeDireito 1424

#define framesSoco 31
#define framesAnda 31

using namespace std;


class Lutador
{
    // Dimensões Corpo
    GLfloat rCabeca;
    GLfloat rNariz;
    GLfloat rMao;
    GLfloat altura;

    GLfloat bracoHeight;
    GLfloat bracoWidth;

    // Angulos
    GLfloat gGiro;

    // GLfloat gThetaDireito1;
    // GLfloat gThetaDireito2;

    // GLfloat gThetaEsquerdo1;
    // GLfloat gThetaEsquerdo2;

    //Posições
    GLfloat gX;
    GLfloat gY;
    GLfloat gZ;

    // Cores RGB
    array<float,3> maoRGB; 
    array<float,3> bracoRGB; 
    array<float,3> cabecaRGB; 

    //3d
    mesh gMesh;
    mesh gMeshInglesVer;

    //Proporcao
    GLfloat gProporcao;
    
    //Bot
    bool gBot;

    //Andar
    GLuint posicao;

    //Soco
    GLuint socoAux = 0;
    GLfloat valorAnterior = 0;

   
private:
    void DesenhaLutador(GLfloat x, GLfloat y, bool modoNoturno);

    bool AcertouCabeca(int braco, Lutador inimigo);

    void SocaBracoDireito(GLfloat angulo1, GLfloat angulo2);

    void SocaBracoEsquerdo(GLfloat angulo1, GLfloat angulo2);

    void DesenhaMesh();
    
    void DesenhaEsferaCabeca();

    void CalculaAlturaLutador();

    GLfloat RaioSombra();

    GLuint LoadTextureRAW( const char * filename );

public:

    Lutador(){
    }

    void Iniciacao(GLfloat x, GLfloat y, GLfloat z, GLfloat angulo, GLfloat raio, bool bot){
        
        array<float,3> maoLutadorRGB = {0.212f, 0.284f, 0.56f};
        array<float,3> bracoLutadorRGB = {0.312f, 0.488f, 0.796f};
        array<float,3> cabecaLutadorRGB =  {0.508,	0.712,	0.96};

        array<float,3> maoBotRGB = {0.016,	0.308, 0.164};
        array<float,3> bracoBotRGB = {0.088, 0.512, 0.228};
        array<float,3> cabecaBotRGB = {0.276, 0.764, 0.34};

        rCabeca = raio;
        gX = x;
        gY = y;
        gZ = z;
        
        gGiro = angulo;

        bracoHeight = rCabeca * 1.5;
        bracoWidth = rCabeca/3;

        rNariz = rCabeca/3;
        rMao = rCabeca/2;

        // gThetaDireito1 = thetaInicial2;
        // gThetaDireito2 = thetaInicial1;

        // gThetaEsquerdo1 = thetaInicial1;
        // gThetaEsquerdo2 = thetaInicial2;

        gBot = bot;

        if(bot)
        {
            maoRGB = maoBotRGB;
            cabecaRGB = cabecaBotRGB;
            bracoRGB = bracoBotRGB;
        }
        else
        {
            maoRGB = maoLutadorRGB;
            cabecaRGB = cabecaLutadorRGB;
            bracoRGB = bracoLutadorRGB;
        }  
      //        gMesh.loadMesh("modelos/socandoDireito/socando_000001.obj");

        gMesh.loadMesh("modelos/walking/walking_000001.obj");
        gMeshInglesVer.loadMesh("modelos/girl.obj");

        raioSombra = RaioSombra();

        gProporcao = rCabeca/raioSombra;
        
        CalculaAlturaLutador();
    };

    GLfloat GetX();

    GLfloat GetY();

    GLfloat GetZ();

    void Desenha(bool modoNoturno){
        DesenhaLutador(gX, gY, modoNoturno);
    }

    void Gira(GLfloat inc);
    
    void Anda(GLfloat dY);
    
    bool Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, Lutador inimigo);
    
    void ParaDeSocar();

    bool VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2);
    
    void GiraSozinho(GLfloat inc, GLfloat xLutador, GLfloat yLutador);
 
    GLfloat GetXFromMesh(GLfloat meshpoint);

    GLfloat GetYFromMesh(GLfloat meshpoint);

    GLfloat GetZFromMesh(GLfloat meshpoint);

    GLfloat GetXFromRealMesh(GLfloat meshpoint);

    GLfloat GetYFromRealMesh(GLfloat meshpoint);

    GLfloat GetZFromRealMesh(GLfloat meshpoint);
    
    GLfloat GetXMeshPuro(GLfloat meshpoint);

    GLfloat GetYMeshPuro(GLfloat meshpoint);

    GLfloat GetZMeshPuro(GLfloat meshpoint);

    void DirecaoPrimeiraPessoa(GLfloat dY, GLfloat ponto[3]);

    void CarregaTexturas();

    GLfloat raioSombra;

};

#endif	/* LUTADOR_H */
