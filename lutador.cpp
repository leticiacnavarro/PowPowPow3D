#include "lutador.h"
#include "ringue.h"
#include <math.h>

GLfloat DistanciaPontos(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    return distanciaPontos;
}

void GetVectorMiddle(GLfloat a[3], GLfloat b[3], GLfloat c[3]){    

    c[0] = a[0] - b[0];
    c[1] = a[1] - b[1];
    c[2] = a[2] - b[2];

    c[0] = c[0]/2;
    c[1] = c[1]/2;
    c[2] = c[2]/2;

    c[0] = c[0] + b[0];
    c[1] = c[1] + b[1];
    c[2] = c[2] + b[2];
}


void Lutador::DesenhaEsferaCabeca(){

    GLfloat pontoX = gMesh.vertsPos[pontoOlho].x;
    GLfloat pontoY = gMesh.vertsPos[pontoOlho].y;

    GLfloat a[3] = { GetXFromRealMesh(pontoOlho), GetYFromRealMesh(pontoOlho), GetZFromRealMesh(pontoOlho)};
    GLfloat b[3] = { GetXFromRealMesh(pontoCabecaAtras), GetYFromRealMesh(pontoCabecaAtras), GetZFromRealMesh(pontoCabecaAtras)};
    GLfloat c[3];

    GetVectorMiddle(a, b, c);
    GLfloat raio = DistanciaPontos(a[0], a[1], b[0], b[1]);
    glPushMatrix();
        glTranslatef(pontoX, pontoY, c[2]);
        glutSolidSphere (raio, 20, 16);
    glPopMatrix();



    GLfloat pontoMao;
    GLfloat pontoPulso;    

    pontoMao = pontoMaoDireita;
    pontoPulso = pontoPulsoDireito;


    GLfloat maoA[3] = { GetXFromRealMesh(pontoMao), GetYFromRealMesh(pontoMao), GetZFromRealMesh(pontoMao)};
    GLfloat maoB[3] = { GetXFromRealMesh(pontoPulso), GetYFromRealMesh(pontoPulso), GetZFromRealMesh(pontoPulso)};
    GLfloat maoC[3];
    GetVectorMiddle(maoA, maoB, maoC);
    GLfloat pontoX2 = gMesh.vertsPos[pontoMao].x;
    GLfloat pontoY2 = gMesh.vertsPos[pontoMao].y;
    GLfloat raio2 = DistanciaPontos(maoA[0], maoA[1], maoB[0], maoB[1]);

    glPushMatrix();
        glTranslatef(pontoX2, pontoY2, maoC[2]);
        glutSolidSphere (raio2, 20, 16);
    glPopMatrix();
}

void Lutador::DesenhaMesh()
{
    glPushMatrix();
        glScaled(gProporcao, gProporcao, gProporcao);
        gMesh.draw();
    glPopMatrix();

}

GLfloat Lutador::RaioSombra()
{
    GLfloat pontoX = gMesh.vertsPos[pontoPeEsquerdo].x;
    GLfloat pontoY = gMesh.vertsPos[pontoPeEsquerdo].y;

    GLfloat pontoX2 = gMesh.vertsPos[pontoPeDireito].x;
    GLfloat pontoY2 = gMesh.vertsPos[pontoPeDireito].y;

    GLfloat raio = (DistanciaPontos(pontoX, pontoY, pontoX2, pontoY2));

    return raio;
}


void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glDisable(GL_LIGHTING);    
   
    int pts = 50;
    glColor4f (R, G, B, 0.2);

    for(unsigned int i = 0; i <= pts; ++i ){

        float angle = ( i / (float)pts ) * 3.14159f * 2.0f;
        float x = radius * sin(angle);
        float y = radius * cos(angle);
        
        glPointSize(3);

        glBegin(GL_POLYGON);
            glVertex3f(x, y, 0.0f);
    }
    glEnd();
    glEnable(GL_LIGHTING);
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
void Lutador::DesenhaLutador(GLfloat x, GLfloat y, bool modoNoturno)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    glRotatef(gGiro, 0, 0, 1);
    GLuint textureSun;

    // if(modoNoturno){
    //     DesenhaCirc((raioSombra), 1, 1, 1);
    // }

    DesenhaMesh();    
 //   DesenhaEsferaCabeca();

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

GLfloat RotateX(GLfloat x, GLfloat y, GLfloat angle){

    GLfloat angle2 = angle * (3.14/180);

    GLfloat xl = (cos(angle2) * x) - (y * sin(angle2));
    GLfloat yl = (sin(angle2) * x) + (y * cos(angle2));

    return xl;
}

GLfloat RotateY(GLfloat x, GLfloat y, GLfloat angle){

    GLfloat angle2 = angle * (3.14/180);

    GLfloat xl = (cos(angle2) * x) - (y * sin(angle2));
    GLfloat yl = (sin(angle2) * x) + (y * cos(angle2));

    return yl;
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
 
    DirecaoNariz(raioSombra, gGiro, gX, gY, xOut, yOut, dY);

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
//  cout << "gX X: " << gX <<endl;
}

void Lutador::DirecaoPrimeiraPessoa(GLfloat dY, GLfloat ponto[3])
{     
    GLfloat xOut;
    GLfloat yOut;
 
    DirecaoNariz(raioSombra, gGiro, gX, gY, xOut, yOut, dY);

    ponto[0] = xOut;
    ponto[1] = yOut;
    ponto[2] = 250;

}



bool Lutador::AcertouCabeca(int braco, Lutador inimigo)
{
    
    GLfloat pontoMao;
    GLfloat pontoPulso;    

    if(braco == 1){
        pontoMao = pontoMaoDireita;
        pontoPulso = pontoPulsoDireito;
    }
    else{
        pontoMao = pontoMaoEsquerda;
        pontoPulso = pontoPulsoEsquerdo;
    }

    GLfloat maoA[3] = { GetXFromRealMesh(pontoMao), GetYFromRealMesh(pontoMao), GetZFromRealMesh(pontoMao)};
    GLfloat maoB[3] = { GetXFromRealMesh(pontoPulso), GetYFromRealMesh(pontoPulso), GetZFromRealMesh(pontoPulso)};
    GLfloat maoC[3];



    GLfloat cabecaA[3] = { inimigo.GetXFromRealMesh(pontoOlho), inimigo.GetYFromRealMesh(pontoOlho), inimigo.GetZFromRealMesh(pontoOlho)};
    GLfloat cabecaB[3] = { inimigo.GetXFromRealMesh(pontoCabecaAtras), inimigo.GetYFromRealMesh(pontoCabecaAtras), inimigo.GetZFromRealMesh(pontoCabecaAtras)};
    GLfloat cabecaC[3];
    
    GetVectorMiddle(cabecaB, cabecaA, cabecaC);
    GetVectorMiddle(maoA, maoB, maoC);
    
    GLfloat pontoX = gMesh.vertsPos[pontoMao].x;
    GLfloat pontoY = gMesh.vertsPos[pontoMao].y;

    GLfloat pontoX2 = inimigo.gMesh.vertsPos[pontoOlho].x;
    GLfloat pontoY2 = inimigo.gMesh.vertsPos[pontoOlho].y;

    cabecaC[0] = cabecaC[0];
    cabecaC[1] = cabecaC[1];   
    cabecaC[2] = cabecaC[2];

    // maoC[0] = maoC[0] + GetX();
    // maoC[1] = maoC[1] + GetY();   
    // maoC[2] = maoC[2] + GetZ();

    // cout << "cabecaC X: " << cabecaC[0] <<" - y: " << cabecaC[1] <<endl;
    // cout << "maoC X: " << maoC[0] <<" - y: " << maoC[1] << endl;
    GLfloat dist = DistanciaPontos(cabecaA[0], cabecaA[1], cabecaB[0], cabecaB[1]);
    GLfloat raioMinimo = dist + (dist/2);
    GLfloat distanciaMaoCabeca = DistanciaPontos(maoC[0], maoC[1], cabecaC[0], cabecaC[1]);
    // cout << "distanciaMaoCabeca " << distanciaMaoCabeca << endl;
    // cout << "raioMinimo " << raioMinimo << endl;
    if(raioMinimo > distanciaMaoCabeca){

        return true;
    }    
   
    return false;
}

bool Lutador::VerificaSePode(GLfloat dY, GLfloat xArena, GLfloat yArena, GLfloat xLutador2, GLfloat yLutador2){
 
    // Quadrado
    if(xArena > yArena){
        yArena = xArena;
    }

    if(yArena > xArena){
        xArena = yArena;
    }
    GLfloat xOut;
    GLfloat yOut;

    DirecaoNariz(raioSombra, gGiro, gX, gY, xOut, yOut, dY);

    GLfloat yColisaoLutador = gY + dY + (raioSombra);
    GLfloat xColisaoLutador = gX + (raioSombra);

    GLfloat distanciaPontos = DistanciaPontos(xOut, yOut, xLutador2, yLutador2);
    GLfloat distancia = raioColisao * 5;

    yArena = (yArena / 2) - (raioSombra/2);
    xArena = (xArena / 2) - (raioSombra/2);

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

void Lutador::CalculaAlturaLutador(){

    GLfloat z1 = gMesh.vertsPos[pontoMeioCabeca].z * gProporcao;
    GLfloat z2 = gMesh.vertsPos[pontoPeDireito].z * gProporcao;

    altura = z1 - z2;
}


bool Lutador::Soca(GLfloat distanciaTotal, GLfloat distanciaPercorrida, GLint braco, Lutador inimigo){
    
    GLint contagem = (distanciaPercorrida * framesSoco)/distanciaTotal;
         

    if(contagem < 1){
        contagem = 1;
    }
    
    // cout << "contagem: " << contagem <<endl;
    
    if(contagem > framesSoco){
        contagem = framesSoco;
    }
    std::string frame = std::string(2 - to_string(contagem).length(), '0') + to_string(contagem);
    std::string objFrame;
    if(braco == 1)
    {
        objFrame = "modelos/direito/direito_0000" + frame + ".obj";
    }
    else
    {
        objFrame = "modelos/esquerdo/esquerdo_0000" + frame + ".obj";
    }

    gMesh.loadMesh(objFrame);

    bool fezPonto = AcertouCabeca(braco, inimigo);
    
    return fezPonto;
}


void Lutador::ParaDeSocar()
{    
   // gMesh.loadMesh("modelos/walking/walking_000001.obj");
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
GLfloat Lutador::GetXFromMesh(GLfloat meshpoint)
{
    GLfloat point = RotateX(gMeshInglesVer.vertsPos[meshpoint].x, gMeshInglesVer.vertsPos[meshpoint].y, gGiro);
    return point*gProporcao + gX;
}
GLfloat Lutador::GetYFromMesh(GLfloat meshpoint)
{
    GLfloat point = RotateY(gMeshInglesVer.vertsPos[meshpoint].x, gMeshInglesVer.vertsPos[meshpoint].y, gGiro);
    return point*gProporcao + gY;}

GLfloat Lutador::GetZFromMesh(GLfloat meshpoint)
{
    return gMeshInglesVer.vertsPos[meshpoint].z*gProporcao + gZ;
}

GLfloat Lutador::GetXFromRealMesh(GLfloat meshpoint)
{
    GLfloat point = RotateX(gMesh.vertsPos[meshpoint].x, gMesh.vertsPos[meshpoint].y, gGiro);
    return (point*gProporcao + gX);
}
GLfloat Lutador::GetYFromRealMesh(GLfloat meshpoint)
{
    GLfloat point = RotateY(gMesh.vertsPos[meshpoint].x, gMesh.vertsPos[meshpoint].y, gGiro);
    return (point*gProporcao + gY) ;
}
GLfloat Lutador::GetZFromRealMesh(GLfloat meshpoint)
{
    return (gMesh.vertsPos[meshpoint].z*gProporcao + gZ);
}
GLfloat Lutador::GetXMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].x;
}
GLfloat Lutador::GetYMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].y;
}
GLfloat Lutador::GetZMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].z;
}

GLfloat Lutador::GetXMeshNormal(GLfloat meshpoint)
{
    return gMesh.vertsNorm[meshpoint].x;
}
GLfloat Lutador::GetYMeshNormal(GLfloat meshpoint)
{
    return gMesh.vertsNorm[meshpoint].y;
}
GLfloat Lutador::GetZMeshNormal(GLfloat meshpoint)
{
    return gMesh.vertsNorm[meshpoint].z;
}
