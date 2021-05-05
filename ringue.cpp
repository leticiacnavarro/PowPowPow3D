#include "ringue.h"

#include <math.h>

GLuint Ringue::LoadTextureRAW( const char * filename )
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


void Ringue::DefineTamanhoLadoTotal()
{
    GLfloat x1 = gMesh.vertsPos[pontoBase1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBase1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBase2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBase2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    ladoTotal = (int)distanciaPontos;

}


void Ringue::DefineTamanhoLado()
{
    GLfloat x1 = gMesh.vertsPos[pontoBaseInterno1].x;
    GLfloat y1 = gMesh.vertsPos[pontoBaseInterno1].y;

    GLfloat x2 = gMesh.vertsPos[pontoBaseInterno2].x;
    GLfloat y2 = gMesh.vertsPos[pontoBaseInterno2].y;

    GLfloat distanciaPontos = pow((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) ,0.5);
    lado = (int)distanciaPontos;

}

void Ringue::DefineAltura()
{
    GLfloat p1 = gMesh.vertsPos[pontoBase1].z;
    GLfloat p2 = gMesh.vertsPos[pontoBaseInterno1].z;

    altura = p2 - p1;
    cout << altura << endl;
}

void Ringue::DesenhaRingue()
{
    glPushMatrix();
        glTranslatef(0, 0, -altura);
        glScalef(gProporcao, gProporcao, gProporcao);
        gMesh.draw();
    glPopMatrix();

}

void Ringue::CarregaTexturas()
{
    gMesh.loadTextura(LoadTextureRAW("modelos/ringue.bmp")); 
}

GLfloat Ringue::GetXMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].x * gProporcao;
}

GLfloat Ringue::GetYMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].y * gProporcao;
}

GLfloat Ringue::GetZMeshPuro(GLfloat meshpoint)
{
    return gMesh.vertsPos[meshpoint].z * gProporcao;
}