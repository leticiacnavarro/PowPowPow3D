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
#define pontoOlho 1619
#define pontoBraco 2108
#define framesSoco 15
using namespace std;


class Lutador
{
    // Dimensões Corpo
    GLfloat rCabeca;
    GLfloat rNariz;
    GLfloat rMao;

    GLfloat bracoHeight;
    GLfloat bracoWidth;

    // Angulos
    GLfloat gGiro;

    GLfloat gThetaDireito1;
    GLfloat gThetaDireito2;

    GLfloat gThetaEsquerdo1;
    GLfloat gThetaEsquerdo2;

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

    //Proporcao
    GLfloat gProporcao;

    //Bot
    bool gBot;
private:
    void DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B);

    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);

    void DesenhaCabeca(GLfloat x, GLfloat y);

    void DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2);

    void DesenhaLutador(GLfloat x, GLfloat y);

    bool AcertouCabeca(GLfloat inimigox, GLfloat inimigoy, int braco);

    void SocaBracoDireito(GLfloat angulo1, GLfloat angulo2);

    void SocaBracoEsquerdo(GLfloat angulo1, GLfloat angulo2);

    void DesenhaMesh();

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

        gThetaDireito1 = thetaInicial2;
        gThetaDireito2 = thetaInicial1;

        gThetaEsquerdo1 = thetaInicial1;
        gThetaEsquerdo2 = thetaInicial2;

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

        gMesh.loadMesh("modelos/girl.obj");
    };

    GLfloat GetX();

    GLfloat GetY();

    GLfloat GetZ();

    void Desenha(){
        DesenhaLutador(gX, gY);
    }

    void Gira(GLfloat inc);
    
    void Anda(GLfloat dY);
    
    bool Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, GLfloat inimigox, GLfloat inimigoy);
    
    void ParaDeSocar();

    bool VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2);
    
    void GiraSozinho(GLfloat inc, GLfloat xLutador, GLfloat yLutador);
 
    GLfloat GetXFromMesh(GLfloat meshpoint);

    GLfloat GetYFromMesh(GLfloat meshpoint);

    GLfloat GetZFromMesh(GLfloat meshpoint);

    void DirecaoPrimeiraPessoa(GLfloat dY, GLfloat ponto[3]);
};

#endif	/* LUTADOR_H */
