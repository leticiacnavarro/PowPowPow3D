#include "lutador.h"
#include "ringue.h"
#include <math.h>

void Lutador::DesenhaMesh()
{
    glPushMatrix();
        //glScaled(5, 5, 5);
        gMesh.draw();
    glPopMatrix();

}

GLuint Lutador::LoadTextureRAW( const char * filename )
{

    GLuint texture;
    
    Image* image = loadBMP(filename);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                             0,                            //0 for now
                             GL_RGB,                       //Format OpenGL uses for image
                             image->width, image->height,  //Width and height
                             0,                            //The border of the image
                             GL_RGB, //GL_RGB, because pixels are stored in RGB format
                             GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                               //as unsigned numbers
                             image->pixels);               //The actual pixel data
    delete image;

    return texture;
}


void Lutador::CarregaTexturas()
{
    if(gBot)
    {
       gMesh.loadTextura(LoadTextureRAW("modelos/girl2.bmp")); 

    }
    else{
        gMesh.loadTextura(LoadTextureRAW("modelos/girl.bmp")); 
    }
}
void Lutador::DesenhaLutador(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glRotatef(gGiro, 0, 0, 1);
    GLuint textureSun;


    DesenhaMesh();        

    glPopMatrix();
}



//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

    GLfloat angle2 = angle * (3.14/180);

    GLfloat xl = (cos(angle2) * x) - (y * sin(angle2));
    GLfloat yl = (sin(angle2) * x) + (y * cos(angle2));

    xOut = xl;
    yOut = yl;    

}

//Função pra ver aonde tá apontando o nariz
void DirecaoNariz(GLfloat raio, GLfloat angulo, GLfloat gx, GLfloat gy, GLfloat &x, GLfloat &y, GLfloat dy)
{
    
    GLfloat xOut;
    GLfloat yOut;
 
    GLfloat xAux = 0;
    GLfloat yAux = dy;

    RotatePoint(xAux, yAux, angulo, xOut, yOut);
   // printf("angulo %0.2f  \n", angulo);

    x = xOut + gx;
    y = yOut + gy;

    

}
void Lutador::Gira(GLfloat inc)
{
    if(inc > 0)
    {
        gGiro++;
        if(gGiro > 360){
            gGiro = 1;
        }

    }
    else{
        gGiro--;
        if(gGiro < 0){
            gGiro = 359;
        }
    }


}
void Lutador::Anda(GLfloat dY)
{     
    GLfloat xOut;
    GLfloat yOut;
 
    DirecaoNariz(rCabeca, gGiro, gX, gY, xOut, yOut, dY);

    gX = xOut;
    gY = yOut;

    posicao++;

    if(posicao > framesAnda){
        posicao = 1;
    }
    std::string frame = std::string(2 - to_string(posicao).length(), '0') + to_string(posicao);
    std::string objFrame;
    objFrame = "modelos/andar/andar_0000" + frame + ".obj";
    gMesh.loadMesh(objFrame);

}

void Lutador::DirecaoPrimeiraPessoa(GLfloat dY, GLfloat ponto[3])
{     
    GLfloat xOut;
    GLfloat yOut;
 
    DirecaoNariz(rCabeca, gGiro, gX, gY, xOut, yOut, dY);

    ponto[0] = xOut;
    ponto[1] = yOut;
    ponto[2] = 250;

}

GLfloat DistanciaPontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    return distanciaPontos;
}

bool Lutador::AcertouCabeca(GLfloat inimigox, GLfloat inimigoy, int braco)
{

    GLfloat angulo1;
    GLfloat angulo2;
    GLfloat distBraco;
       

    if(braco == 1)
    {
        angulo1 = gThetaDireito2;
        angulo2 = gThetaDireito1;
        distBraco = rCabeca;
    }

    else
    {
        angulo1 = gThetaEsquerdo2;
        angulo2 = gThetaEsquerdo1;
        distBraco = -rCabeca;
    }

        GLfloat xOut;
        GLfloat yOut;
    
        GLfloat xAux = 0;
        GLfloat yAux = rMao + bracoHeight;

        GLfloat distanciaSoco =  rMao + rCabeca;            


        RotatePoint(xAux, yAux, angulo1, xOut, yOut);

        xAux = xOut;
        yAux = yOut + bracoHeight;

        RotatePoint(xAux, yAux, angulo2, xOut, yOut);

        xAux = xOut + distBraco;
        yAux = yOut;

        RotatePoint(xAux, yAux, gGiro, xOut, yOut);    

        xAux = xOut + gX;
        yAux = yOut + gY;

        GLfloat distanciaPontos =  DistanciaPontos(xAux, yAux, inimigox, inimigoy);            

      //  printf("Distancia Soco %0.2f  \n", distanciaSoco);
      //  printf("Distancia Pontos %0.2f  \n", distanciaPontos);

    if(distanciaPontos < distanciaSoco){
        return true;
    }
    
    return false;
}

bool Lutador::VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2){
 
    GLfloat xOut;
    GLfloat yOut;

    DirecaoNariz(rCabeca, gGiro, gX, gY, xOut, yOut, dY);

    GLfloat yColisaoLutador = gY + dY + (rCabeca * 3);
    GLfloat xColisaoLutador = gX + (rCabeca * 3);

    GLfloat distanciaPontos = DistanciaPontos(xOut, yOut, xLutador2, yLutador2);
    GLfloat distancia = raioColisao * 3.5;

    yArena = ladoRingue - raioColisao;
    xArena = ladoRingue - raioColisao;

    if(yOut > (yArena))
        return false;
    
    if(yOut < -(yArena))
        return false;

    if(xOut > (xArena))
        return false;
    
    if(xOut < -(xArena))
        return false;

    if(distanciaPontos < distancia){
        return false;
    }
    else{
        return true;
    } 

    return true;
}

void Lutador::SocaBracoDireito(GLfloat angulo1, GLfloat angulo2){
    gThetaDireito1 = angulo1;
    gThetaDireito2 = angulo2;

}


void Lutador::SocaBracoEsquerdo(GLfloat angulo1, GLfloat angulo2){
    gThetaEsquerdo1 = angulo1;
    gThetaEsquerdo2 = angulo2;
}

bool Lutador::Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, GLfloat inimigox, GLfloat inimigoy){
    
    GLint contagem = (distanciaPercorrida * framesSoco)/ distanciaTotal;
    if(contagem < 1)
    {
        contagem = 1;
    }
    std::string frame = std::string(2 - to_string(contagem).length(), '0') + to_string(contagem);
    std::string objFrame;
    if(braco == 1)
    {
        objFrame = "modelos/socoDireito/untitled_0000" + frame + ".obj";
    }
    else
    {
        objFrame = "modelos/socoEsquerdo/socoEsquerdo_0000" + frame + ".obj";
    }

   // cout << contagem <<  endl;
    // cout << "distanciaPercorrida " << distanciaPercorrida <<  endl;
    // cout << "distanciaTotal " << distanciaTotal <<  endl;

    // cout << "contagem " << contagem <<  endl;

    gMesh.loadMesh(objFrame);

    // bool fezPonto = AcertouCabeca(inimigox, inimigoy, braco);
    
    if(contagem >= 17){
        return true;
    }
    return false;
}


void Lutador::ParaDeSocar()
{
    SocaBracoEsquerdo(135, 225);
    SocaBracoDireito(225, 135);

}

GLfloat Lutador::GetX(){
    return gX;
}

GLfloat Lutador::GetY(){
    return gY;
}

GLfloat Lutador::GetZ(){
    return gZ;
}

GLfloat CalculaCoeficienteCabecas(GLfloat gXLutador, GLfloat gYLutador, GLfloat gX, GLfloat gY){

    GLfloat deltaX = abs(gXLutador - gX);
    GLfloat deltaY = abs(gYLutador - gY);

    GLfloat tangente = deltaX/deltaY;
    GLfloat angulo = (atan (tangente) * 180 / 3.14);

    if(gY > gYLutador && gXLutador > gX)
    {
        angulo = 180 + angulo;
    }
    
    else if(gY > gYLutador && gX > gXLutador)
    {
        angulo = 90 + angulo;
    }
    
    else if(gX == gXLutador && gY > gYLutador)
    {
        angulo = 180 + angulo;
    }
    
    else if(gYLutador > gY && gXLutador > gX)
    {
        angulo = 360 - angulo;
    }
    
    else if(gYLutador ==  gY && gXLutador > gX)
    {
        angulo = 180 + angulo;
    }

    return angulo;
}

void Lutador::GiraSozinho(GLfloat inc, GLfloat xLutador, GLfloat yLutador)
{
    GLfloat anguloLutador = CalculaCoeficienteCabecas(xLutador, yLutador, gX, gY);

    gGiro = anguloLutador;
}
GLfloat Lutador::GetXFromMesh(GLfloat meshpoint){
   // cout << "x" << gMesh.vertsPos[meshpoint].z << endl;

    return gMeshInglesVer.vertsPos[meshpoint].x + gX;
}
GLfloat Lutador::GetYFromMesh(GLfloat meshpoint){
     //   cout << "y" << gMesh.vertsPos[meshpoint].z << endl;

    return gMeshInglesVer.vertsPos[meshpoint].y + gY;
}
GLfloat Lutador::GetZFromMesh(GLfloat meshpoint){
   // cout << "z" << gMesh.vertsPos[meshpoint].z << endl;
    return gMeshInglesVer.vertsPos[meshpoint].z + gZ;
}
