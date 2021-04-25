#ifndef INICIACAO_H
#define	INICIACAO_H

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "tinyxml/tinyxml.h"
#include "lutador.h"

using namespace std;

class Iniciacao
{

    // Lutador

    GLfloat gXLutador;
    GLfloat gYLutador;
    GLfloat gGiroLutador;
    GLfloat rCabecaLutador;

    // Bot

    GLfloat gXBot;
    GLfloat gYBot;
    GLfloat gGiroBot;
    GLfloat rCabecaBot;

    // Arena

    GLfloat width;
    GLfloat height;
 
    GLfloat widthHalf;
    GLfloat heightHalf;

    GLfloat xArena;
    GLfloat yArena;

private:
    void ProcessaArena(TiXmlElement *arena);
 
    void ProcessaLutadores(TiXmlElement *lutador1, TiXmlElement *lutador2);
  
    void ProcessaBot(TiXmlElement *arena);
 
    string ObtemNomeArquivo();
  

    void CalculaCoeficienteCabecas();

public:
    Iniciacao(){}
    bool ProcessaArquivo(char* nomeArquivo);

    void IniciaLutadores(Lutador &lutador, Lutador &bot);

    void IniciaArena(GLint &widthArena, GLint &heightarena, GLint &widthHalfArena, GLint &heightHalfarena);

    void TipoJogo(bool &modoTreino);

};

#endif	/* ROBO_H */
